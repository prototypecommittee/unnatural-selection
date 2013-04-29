import math
import serial
import time
import threading
import OSC

oscString ="NOOT"
## OSC Reciever
recieve_address = '127.0.0.1',12345

## SERIAL SENDER
# OSC Server. there are three different types of server. 
ss = OSC.OSCServer(recieve_address)


##s = OSC.ThreadingOSCServer(receive_address) # threading
##s = OSC.ForkingOSCServer(receive_address) # forking

# this registers a 'default' handler (for unmatched messages), 
# an /'error' handler, an '/info' handler.
# And, if the client supports it, a '/subscribe' & '/unsubscribe' handler
ss.addDefaultHandlers()

# define a message-handler function for the server to call.
def printing_handler(addr, tags, stuff, source):
    print "---"
    print "received new osc msg from %s" % OSC.getUrlStr(source)
    print "with addr : %s" % addr
    print "typetags %s" % tags
    print "data %s" % stuff
    print "---"
    str1 = "".join(str(x) for x in stuff)
    global oscString
    oscString = str1
#    global oscString
#oscString = stuff

ss.addMsgHandler("/table", printing_handler) # adding our function

# just checking which handlers we have added
print "Registered Callback-functions are :"
for addr in ss.getOSCAddressSpace():
    print addr


from threading import Thread, Lock
class Serial:
  def __init__(self, port='/dev/tty.usbmodem411', rate=9600, timeout=10):
		self._serial = serial.Serial(port, rate, timeout=timeout)
		self._mutex = Lock()
		self._mutex.acquire()
		response = self._serial.readline().strip()
		if response != 'OK':
			raise Exception("Failed to communicate with the serial device!")
			sys.exit()
		self._mutex.release()

	def _tableCommand(self,command):
		self.serial.write(command)
		response = self._serial.readline()
		return response.strip()
			
	def _shortCommand(self, command):
		self._serial.write(command)
		response = self._serial.readline()
		return response.strip()

	def _longCommand(self, command):
		response = self._shortCommand('RCV ' + str(len(command)) + "\n")
		if response != 'RDY':
			return None
		for i in range(int(math.ceil(len(command) / 128.0))):
			c = command[128*i:128*(i+1)]
			response = self._shortCommand(c)
		return self._serial.readline().strip()

	def command(self, command):
		self._mutex.acquire()
		if len(command) < 128:
			response = self._shortCommand(command + "\n")
		else:
			response = self._longCommand(command)
		self._mutex.release()
		return response

import random, string

def main():
# Start OSCServer
	print "\nStarting OSCServer. Use ctrl-C to quit."
	st = threading.Thread( target = ss.serve_forever )
	st.start()
	
	serial = Serial(port='/dev/tty.usbmodem411', rate=115200)
	passed = 0
	failed = 0
	for i in range(100000):
		l = random.randint(1, 1023)
#		s = ''.join(random.choice(string.ascii_uppercase + string.ascii_lowercase + string.digits) for x in range(l))
		s = oscString
		o = serial.command(s)
		if o == s:
			print ("arduino sez: " + o);
			print (i + 1), 'OK', l, 'bytes'
			passed = passed + 1
		else:
			print ("arduino sez: " + o);
			print (i + 1), 'FAIL', l, 'bytes'
			failed = failed + 1
	print 'Passed:', passed
	print 'Failed:', failed
	
if __name__ == "__main__":
   try:
      main()
   except KeyboardInterrupt:
    print "\nClosing OSCServer."
    ss.close()
    print "Waiting for Server-thread to finish"
    st.join()
    print "Done"
    pass
 
