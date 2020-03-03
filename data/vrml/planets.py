print "planets.py loaded"
#sys.path.append("C:/rami/micole_cvs/micole/solarsystem/data/vrml")
sys.path.append("C:/jouni/micole/solarsystem/data/vrml")

import messagenode
import Insert3DConnexionDevice
import time

global outmessage
global scene

display = getDisplay()
pbl = None
tipColorChanger = None
scene = None
mgAsButton = None
mg = None
initialized = 0
outmessage=messagenode.outmessage
print "a"
print outmessage
scene, = references

time.clock()
print "1"

class TipColorChanger (Dependent(SFVec3f)):
	def __init__(self):
		SFVec3f.__init__(self)
		self.last = 0

	def evaluate(self, inVec):
		display = getDisplay()
		if((inVec.get().z != 0) and (self.last == 0)):
			display.tip.get().appearance.get().material.get().diffuseColor.set(Color(1,1,1))
			self.last = 1;
		elif((inVec.get().z == 0) and (self.last == 1)):
			display.tip.get().appearance.get().material.get().diffuseColor.set(Color(0.3,0.3,0.3))
			self.last = 0;

print "2"
class MagellanButtonTracker( Dependent( MFInt32 ) ):

	#def __init__( self, n ):
	#	MFInt32.__init__(self)
	#	self.num = n

	def evaluate( self, input ):
		global outmessage
		buttons = input.get()
		index = 0
		for x in buttons:
			if(x):
				index = buttons.index(x);
#				print index
				if index is 3:
					outmessage.content.set("OUT COMMENT : command=CURRENT;")
					outmessage.ready.set(1)
#				elif index is 4:
#					outmessage.content.set("OUT COMMENT : command=PREVIOUS;")
#					outmessage.ready.set(1)
				elif index is 9:
					outmessage.content.set("OUT COMMENT : command=NEXT;")
					outmessage.ready.set(1)
				elif index is 2:
					outmessage.content.set("OUT COMMENT : command=EDIT;")
					outmessage.ready.set(1)
				elif index is 1:
					outmessage.content.set("OUT COMMENT : command=OK;")
					outmessage.ready.set(1)
#				elif index is 5:
#					outmessage.content.set("OUT COMMENT : command=CANCEL;")
#					outmessage.ready.set(1)
print "3"

#########################################
#
# Listens the magellans "joystick" if its pushed.
# Sends agent message when triggered.
#
#########################################
class MagellanJoystickAsButton (Dependent(SFVec3f)):
	def __init__(self):
		SFVec3f.__init__(self)
		self.prev = 0
		self.tval = time.clock()
	def evaluate(self, input):
		global outmessage
		coords = str(input.get())
		temp, x, y, z, temp2 = coords.split()
#		print temp, x, y, z, temp2
		if(float(z) > 0.007):
			push = 1
		else:
			push = 0

#		print push, self.prev
		if (push != self.prev and push == 1 and (time.clock()-self.tval) > 1.0):
			omsg = "IN SA : cmd=load;obj=SOLARSYSTEM;"
			outmessage.content.set(omsg)
			outmessage.ready.set(1)
			self.tval = time.clock()

#		else:
#			control.magellanRelease()
		push = 0
		self.prev = push

print "4"
#########################################
#
# Listens PHANTOMs button.
#
#########################################
class PhantomButtonListener(Dependent(SFBool)):
	def evaluate(self, inBool):
		if(inBool.get() == 1):
			omsg = "IN SA : cmd=teach;obj=empty;"
			outmessage.content.set(omsg)
			outmessage.ready.set(1)

print "5"

class Initializer(Dependent(SFBool)):
	def evaluate(self,input):
		global display
		global outmessage
		global initalized
		initialized = 0
		if input.get():
			if(initialized == 0 ):
				initializem()
				#print "Input get ", display
				#.children.get()
				#
				if(outmessage is None):
					for x in display.children.get():
						print "looking at: " + str(x)
						messagenode.getMessageNode(x)
				outmessage=messagenode.outmessage
				outmessage.ready.set(0)
				print "xxx: " + str(outmessage)


class Finalizer(Dependent(SFBool)):
	def evaluate(self,input):
		if input.get():
			finalize()

def initializem():
	global initialized

	global mg
	global mgBT
	global mgAsButton
	global pbl
	global tipColorChanger

	display = getDisplay()

	pbl = PhantomButtonListener()
	display.button.route(pbl)

	tipColorChanger = TipColorChanger()
	scene.hapticForce.route(tipColorChanger)

	mg = Insert3DConnexionDevice.insert()
	mgAsButton = MagellanJoystickAsButton()
	mg.instantTranslation.route(mgAsButton)

	mgBT = MagellanButtonTracker()
	mg.buttons.route(mgBT)

	initialized = 1


def finalize():
	global initialized
	global pbl
	global tipColorChanger
	global mgAsButton
	global mgBT
	global mg
	global outmessage

	display = getDisplay()
	display.button.unroute(pbl)
	scene.hapticForce.unroute(tipColorChanger)
	mg.instantTranslation.unroute(mgAsButton)
	mg.buttons.unroute(mgBT)
	initialized = 0


initializer = Initializer()
finalizer = Finalizer()

