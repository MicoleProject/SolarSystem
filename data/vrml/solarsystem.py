print "solarsystem.py ladattu"
#sys.path.append("C:/rami/micole_cvs/micole/solarsystem/data/vrml")
sys.path.append("C:/jouni/micole/solarsystem/data/vrml")

from math import *
#import Keyboard
import messagenode
import Insert3DConnexionDevice
#from time import time

display = getDisplay()
#print display.children.get()

global scene
global outmessage
global solarSystem

mercuryButton = None
venusButton = None
earthButton = None
marsButton = None
jupiterButton = None
saturnButton = None
uranusButton = None
neptuneButton = None
plutoButton = None

sun = None
mercury = None
venus = None
earth = None
mars = None
jupiter = None
saturn = None
uranus = None
neptune = None
pluto = None
mercuryOrbit = None
venusOrbit = None
earthOrbit = None
marsOrbit = None
jupiterOrbit = None
saturnOrbit = None
uranusOrbit = None
neptuneOrbit = None
plutoOrbit = None
tipColorChanger = None
mg = None
mgAsButton  = None

#---------------------------------------------------------
import threading
global lock
lock =threading.Lock()
#---------------------------------------------------------

#for x in display.children.get():
#	messagenode.getMessageNode(x)

print "1"
outmessage=messagenode.outmessage

print outmessage

class SolarSystem:
	def __init__(self):
		self.onOrbit = -1
		self.objects={}
		self.objects[0] = 'SUN'
		self.objects[1] = 'MERCURY'
		self.objects[2] = 'VENUS'
		self.objects[3] = 'EARTH'
		self.objects[4] = 'MARS'
		self.objects[5] = 'JUPITER'
		self.objects[6] = 'SATURN'
		self.objects[7] = 'URANUS'
		self.objects[8] = 'NEPTUNE'
		self.objects[9] = 'PLUTO'

		self.objects[11] = 'MERCURY'
		self.objects[12] = 'VENUS'
		self.objects[13] = 'EARTH'
		self.objects[14] = 'MARS'
		self.objects[15] = 'JUPITER'
		self.objects[16] = 'SATURN'
		self.objects[17] = 'URANUS'
		self.objects[18] = 'NEPTUNE'
		self.objects[19] = 'PLUTO'

		self.objects[21] = 'MERCURY'
		self.objects[22] = 'VENUS'
		self.objects[23] = 'EARTH'
		self.objects[24] = 'MARS'
		self.objects[25] = 'JUPITER'
		self.objects[26] = 'SATURN'
		self.objects[27] = 'URANUS'
		self.objects[28] = 'NEPTUNE'
		self.objects[29] = 'PLUTO'

		#self.objects[11] = 'MERCURY_ORBIT'
		#self.objects[12] = 'VENUS_ORBIT'
		#self.objects[13] = 'EARTH_ORBIT'
		#self.objects[14] = 'MARS_ORBIT'
		#self.objects[15] = 'JUPITER_ORBIT'
		#self.objects[16] = 'SATURN_ORBIT'
		#self.objects[17] = 'URANUS_ORBIT'
		#self.objects[18] = 'NEPTUNE_ORBIT'
		#self.objects[19] = 'PLUTO_ORBIT'

		#self.objects[21] = 'MERCURY_EXTRA'
		#self.objects[22] = 'VENUS_EXTRA'
		#self.objects[23] = 'EARTH_EXTRA'
		#self.objects[24] = 'MARS_EXTRA'
		#self.objects[25] = 'JUPITER_EXTRA'
		#self.objects[26] = 'SATURN_EXTRA'
		#self.objects[27] = 'URANUS_EXTRA'
		#self.objects[28] = 'NEPTUNE_EXTRA'
		#self.objects[29] = 'PLUTO_EXTRA'

	def orbitEntered(self,orbit):
		global outmessage

		if(not self.onOrbit == orbit):
			self.onOrbit = orbit
			print "orbitEntered("+ self.objects[orbit] +")"
			omsg = "IN SA : obj=" + self.objects[orbit] + ";type=ORBIT;"
			outmessage.content.set(omsg)
			outmessage.ready.set(1)


	def planetEncountered(self, planet):
		global outmessage
		print "planetEncountered("+ self.objects[planet] +")"
		omsg = "IN SA : obj="+self.objects[planet]+";type=PLANET;"
		outmessage.content.set(omsg)
		outmessage.ready.set(1)



print "2"

class OrbitTool(Dependent (SFTime)):
	def __init__(self, x, y, scale, sIndex):
		SFTime.__init__(self)
		#SFVec3f.__init__(self)
		self.x = pow(x*scale,2)
		self.y = pow(y*scale,2)
		self.sIndex = sIndex
		self.active = False
	def evaluate(self, input):
		global solarSystem
		#global display
		dis = getDisplay()
		#if dis == None:
		#	return
		global lock
		global outmessage
		#print "orbitTool ", display
		xPos = dis.trackerPosition.get().x
		yPos = dis.trackerPosition.get().y
		zPos = dis.trackerPosition.get().z
		#print xPos," ",yPos, " ", zPos
		a = pow(xPos,2)/self.x + pow(yPos,2)/self.y
		if 0.95 < a and a < 1.05 and zPos < 0.02:
			solarSystem.orbitEntered(self.sIndex)


print "3"

class MagnetTool(Dependent(SFBool)):
	def __init__(self,sIndex=0):
		SFBool.__init__(self)
		self.sIndex = sIndex
	def evaluate(self,input):
		global solarSystem
		#print "magnettool", str(input.get())
		global outmessage
		global lock
		if input.get():
			solarSystem.planetEncountered(self.sIndex)


print "4"
#############################################################
#
# ButtonTool listens to the events of the BUMP_BUTTON
# ButtonBumpmapSurface
#
#############################################################
class ButtonTool ( Dependent(SFBool)):
	def __init__ (self, sIndex, planetMagnet):
		SFBool.__init__(self)
		self.sIndex = sIndex
		self.planet = planetMagnet
		self.pressed = 0

	def evaluate(self, input):
		print "buttontool", input
		global solarSystem
		global outmessage
		if input.get():
			if self.planet.grasping.get():
				if self.pressed == 0:
					solarSystem.planetEncountered(self.sIndex)
					omsg = "IN SA : cmd=load;obj=" + solarSystem.objects[self.sIndex] +";"
					outmessage.content.set(omsg)
					outmessage.ready.set(1)
					self.pressed = 1


print "5"

class TipColorChanger (Dependent(SFVec3f)):
	def __init__(self):
		SFVec3f.__init__(self)
		self.last = 0

	def evaluate(self, inVec):
		if((inVec.get().z != 0) and (self.last == 0)):
			display.tip.get().appearance.get().material.get().diffuseColor.set(Color(1,1,1))
			self.last = 1;
		elif((inVec.get().z == 0) and (self.last == 1)):
			display.tip.get().appearance.get().material.get().diffuseColor.set(Color(0.3,0.3,0.3))
			self.last = 0;

print "6"

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



print "7"
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

print "8"

class Initializer(Dependent(SFBool)):
	def evaluate(self,input):
		global display
		global outmessage
		global solarSystem

		if input.get():
			initializem()
			#print "Input get ", display
			#.children.get()
			for x in display.children.get():
				print x
				messagenode.getMessageNode(x)
			outmessage=messagenode.outmessage
			solarSystem = SolarSystem()
				#outmessage.ready.set(0)
				#print outmessage
print "9"

class Finalizer(Dependent(SFBool)):
	def evaluate(self,input):
		if input.get():
			finalize()
print "10"

def initializem():
	print "solarsystem initialize start"
	global sunTool
	global mercuryButton
	global venusButton
	global earthButton
	global marsButton
	global jupiterButton
	global saturnButton
	global uranusButton
	global neptuneButton
	global plutoButton

	global sun
	global mercury
	global venus
	global earth
	global mars
	global jupiter
	global saturn
	global uranus
	global neptune
	global pluto

	global mercuryOrbit
	global venusOrbit
	global earthOrbit
	global marsOrbit
	global jupiterOrbit
	global saturnOrbit
	global uranusOrbit
	global neptuneOrbit
	global plutoOrbit

	global pbl
	global tipColorChanger
	global mg
	global mgBT

	scene,timer,sunMagnet,mercuryMagnet,venusMagnet,earthMagnet,marsMagnet,jupiterMagnet,saturnMagnet,uranusMagnet,neptuneMagnet,plutoMagnet,bumpButton,sunButton = references

	display = getDisplay()

	sunTool = ButtonTool(0,sunMagnet)
	mercuryButton = ButtonTool(1,mercuryMagnet)
	venusButton = ButtonTool(2,venusMagnet)
	earthButton = ButtonTool(3,earthMagnet)
	marsButton = ButtonTool(4,marsMagnet)
	jupiterButton = ButtonTool(5,jupiterMagnet)
	saturnButton = ButtonTool(6,saturnMagnet)
	uranusButton = ButtonTool(7,uranusMagnet)
	neptuneButton = ButtonTool(8,neptuneMagnet)
	plutoButton = ButtonTool(9,plutoMagnet)
	sunButton.armed.route(sunTool)
	bumpButton.armed.route(mercuryButton)
	bumpButton.armed.route(venusButton)
	bumpButton.armed.route(earthButton)
	bumpButton.armed.route(marsButton)
	bumpButton.armed.route(jupiterButton)
	bumpButton.armed.route(saturnButton)
	bumpButton.armed.route(uranusButton)
	bumpButton.armed.route(neptuneButton)
	bumpButton.armed.route(plutoButton)

	sun = MagnetTool(0)
	mercury = MagnetTool(1)
	venus = MagnetTool(2)
	earth = MagnetTool(3)
	mars = MagnetTool(4)
	jupiter = MagnetTool(5)
	saturn = MagnetTool(6)
	uranus = MagnetTool(7)
	neptune = MagnetTool(8)
	pluto = MagnetTool(9)

	sunMagnet.grasping.route(sun)
	mercuryMagnet.grasping.route(mercury)
	venusMagnet.grasping.route(venus)
	earthMagnet.grasping.route(earth)
	marsMagnet.grasping.route(mars)
	jupiterMagnet.grasping.route(jupiter)
	saturnMagnet.grasping.route(saturn)
	uranusMagnet.grasping.route(uranus)
	neptuneMagnet.grasping.route(neptune)
	plutoMagnet.grasping.route(pluto)

	mercuryOrbit = OrbitTool(10.4,6.8,0.003,11)
	venusOrbit = OrbitTool(13,8.7,0.003,12)
	earthOrbit = OrbitTool(15.3,10,0.003,13)
	marsOrbit = OrbitTool(17.4,12,0.003,14)
	jupiterOrbit = OrbitTool(19.8,13.8,0.003,15)
	saturnOrbit = OrbitTool(22.2,15.6,0.003,16)
	uranusOrbit = OrbitTool(24.3,17.2,0.003,17)
	neptuneOrbit = OrbitTool(26.5,19,0.003,18)
	plutoOrbit = OrbitTool(28.5,20.9,0.003,19)

	#print timer.cycleTime.get()

	timer.cycleTime.route(mercuryOrbit)
	timer.cycleTime.route(venusOrbit)
	timer.cycleTime.route(earthOrbit)
	timer.cycleTime.route(marsOrbit)
	timer.cycleTime.route(jupiterOrbit)
	timer.cycleTime.route(saturnOrbit)
	timer.cycleTime.route(uranusOrbit)
	timer.cycleTime.route(neptuneOrbit)
	timer.cycleTime.route(plutoOrbit)

#	pbl = PhantomButtonListener()
#	display.button.route(pbl)

	tipColorChanger = TipColorChanger()
	scene.hapticForce.route(tipColorChanger)

	mg = Insert3DConnexionDevice.insert()
	mgBT = MagellanButtonTracker()
	mg.buttons.route(mgBT)

	#Keyboard.characters.route( mSelect)
	print "solarsystem initialize end"

print "11"

def finalize():
	print "solarsystem finalize start"
	global mercuryButton
	global venusButton
	global earthButton
	global marsButton
	global jupiterButton
	global saturnButton
	global uranusButton
	global neptuneButton
	global plutoButton

	global sun
	global mercury
	global venus
	global earth
	global mars
	global jupiter
	global saturn
	global uranus
	global neptune
	global pluto

	global mercuryOrbit
	global venusOrbit
	global earthOrbit
	global marsOrbit
	global jupiterOrbit
	global saturnOrbit
	global uranusOrbit
	global neptuneOrbit
	global plutoOrbit

	global tipColorChanger
	global mg
	global mgBT
	global pbl

	global solarSystem

	scene, timer,sunMagnet,mercuryMagnet,venusMagnet,earthMagnet,marsMagnet,jupiterMagnet,saturnMagnet,uranusMagnet,neptuneMagnet,plutoMagnet, bumpButton, sunButton = references

	display = getDisplay()

#	display.button.unroute(pbl)
	scene.hapticForce.unroute(tipColorChanger)
	mg.buttons.unroute(mgBT)

	sunButton.armed.unroute(sunTool)
	bumpButton.armed.unroute(mercuryButton)
	bumpButton.armed.unroute(venusButton)
	bumpButton.armed.unroute(earthButton)
	bumpButton.armed.unroute(marsButton)
	bumpButton.armed.unroute(jupiterButton)
	bumpButton.armed.unroute(saturnButton)
	bumpButton.armed.unroute(uranusButton)
	bumpButton.armed.unroute(neptuneButton)
	bumpButton.armed.unroute(plutoButton)

	#mercuryButton = None
	#venusButton = None
	#earthButton = None
	#marsButton = None
	#jupiterButton = None
	#saturnButton = None
	#uranusButton = None
	#neptuneButton = None
	#plutoButton = None

	sunMagnet.grasping.unroute(sun)
	mercuryMagnet.grasping.unroute(mercury)
	venusMagnet.grasping.unroute(venus)
	earthMagnet.grasping.unroute(earth)
	marsMagnet.grasping.unroute(mars)
	jupiterMagnet.grasping.unroute(jupiter)
	saturnMagnet.grasping.unroute(saturn)
	uranusMagnet.grasping.unroute(uranus)
	neptuneMagnet.grasping.unroute(neptune)
	plutoMagnet.grasping.unroute(pluto)

	sun = None
	mercury = None
	venus = None
	earth = None
	mars = None
	jupiter = None
	saturn = None
	uranus = None
	neptune = None
	pluto = None

	timer.cycleTime.unroute(mercuryOrbit)
	timer.cycleTime.unroute(venusOrbit)
	timer.cycleTime.unroute(earthOrbit)
	timer.cycleTime.unroute(marsOrbit)
	timer.cycleTime.unroute(jupiterOrbit)
	timer.cycleTime.unroute(saturnOrbit)
	timer.cycleTime.unroute(uranusOrbit)
	timer.cycleTime.unroute(neptuneOrbit)
	timer.cycleTime.unroute(plutoOrbit)

	mercuryOrbit = None
	venusOrbit = None
	earthOrbit = None
	marsOrbit = None
	jupiterOrbit = None
	saturnOrbit = None
	uranusOrbit = None
	neptuneOrbit = None
	plutoOrbit = None

	#Keyboard.characters.route( mSelect)
	#solarSystem = None
	print "solarsystem finalize end"


print "12"

initializer = Initializer()
finalizer = Finalizer()

