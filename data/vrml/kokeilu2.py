print "kokeilu jep ladattu"
#sys.path.append("c:/janne/SolarSystemTest/SolarSystemTest/data/vrml")
#sys.path.append("C:/janne/micole_cvs/micole/solarsystem/data/vrml")
#sys.path.append("C:/rami/micole_cvs/micole/solarsystem/data/vrml")
sys.path.append("C:/jouni/micole/solarsystem/data/vrml")
#sys.path.append("urn:micole/python")

from math import *
#import Keyboard
import messagenode
import Insert3DConnexionDevice
#from time import time



display = getDisplay()
#print display.children.get()


global outmessage
global solarSystem
global first_info
global extra_info
global second_info
global orbit_info
first_info = '1'
second_info = '2'
extra_info = '3'
orbit_info = '4'

global effect_sound
global speech_sound
global loop_sound
effect_sound = '1'
speech_sound = '2'
loop_sound = '3'

global magellan
magellan = Insert3DConnexionDevice.insert()
#---------------------------------------------------------
import threading
global lock
lock =threading.Lock()
#---------------------------------------------------------

#for x in display.children.get():
#	messagenode.getMessageNode(x)

#outmessage=messagenode.outmessage

#print outmessage

class MagellanButtonTracker( Dependent( MFInt32 ) ):

	#def __init__( self, n ):
	#	MFInt32.__init__(self)
	#	self.num = n

    def evaluate( self, input ):
    	global outmessage
        buttons = input.get()
        index = 0
        msg = "JEE"
        #omsg2 = None
        for x in buttons:
			if(x):
				index = buttons.index(x);
#				print index
				if index is 1:
					outmessage.content.set("IN SA : cmd=wav;")
					outmessage.ready.set(1)
				elif index is 5:
					outmessage.content.set("IN SA : cmd=syn;")
					outmessage.ready.set(1)
				elif index is 6:
					outmessage.content.set("IN SA : cmd=com;")
					outmessage.ready.set(1)
				elif index is 7:
					outmessage.content.set("IN SA : cmd=read;")
					outmessage.ready.set(1)

bt1 = MagellanButtonTracker()
#magellan.buttons.route(bt1)


#class ModeSelect( Dependent( SFString ) ):
#	def evaluate( self, input ):
#		global outmessage
#		c = input.get()
#		#print input.get(), input.shift, input.control, input.alt
#		#omsg = None
#		if c == 'w':
#			#omsg = "IN SA : mod=wav;"
#			outmessage.content.set("IN SA : mod=wav;")
#			outmessage.ready.set(1)
#			print c
#		elif c == 's':
#			#omsg = "IN SA : mod=syn;"
#			outmessage.content.set("IN SA : mod=syn;")
#			outmessage.ready.set(1)
#   			print c
		#outmessage.content.set(omsg)
		#outmessage.ready.set(1)

#mSelect = ModeSelect()

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

		global lock
		global outmessage
		global orbit_info
		global speech_sound
		#if(self.onOrbit < 10 and self.onOrbit > 0):
		#	return
		if(not self.onOrbit == orbit):
			self.onOrbit = orbit
			print "orbitEntered("+ str(orbit) +")"
			#lock.acquire()
			#omsg = "OUT SPCH: "+self.objects[orbit]+" entered"
			omsg = "IN SA : obj=" + self.objects[orbit] + ";type=" + orbit_info + ";"
			#omsg = "OUT SND : name=Deep Trip - Short 1 Key.wav;type="+speech_sound
			outmessage.content.set(omsg)
			outmessage.ready.set(1)
			#outmessage.ready.touch()
			#lock.release()
			#player.playSound2(self.soundKeys[orbit], 1)


	def planetEncountered(self, planet):

		global outmessage
		global lock
		global first_info
		global second_info
		global extra_info
		global speech_sound
		global effect_sound
		print "planetEncountered("+ str(planet) +")"
		#lock.acquire()
		#omsg = "OUT SPCH: "+self.objects[planet]+" encountered"
		typ = None
		if planet < 10:
			typ = first_info
		else:
			typ = extra_info
			omsg2 = "OUT SND : name=SELECTION_1.WAV;type=" + effect_sound + ";"
			outmessage.content.set(omsg2)
			outmessage.ready.set(1)
		omsg = "IN SA : obj="+self.objects[planet]+";type="+ typ +";"
		#omsg = "OUT SND : type=bground;name=Glimmer - Short 1 Key.wav"
		#^OUT SND : (snd=(.*));;(type=(.*));(pri=(.*))?;(loop=(.*))?;(wait=(.*))
		#omsg = "OUT SND : name=Glimmer - Short 1 Key.wav;type="+effect_sound
		outmessage.content.set(omsg)
		outmessage.ready.set(1)



		#lock.release()
		#player.playSound2(self.soundKeys[planet], 2)
		#sending message to the logger


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

	def evaluate(self, input):
		print "buttontool", input
		#global player
		global solarSystem
		global outmessage
		global lock
		if input.get():
			if self.planet.grasping.get():
				#outmessage.content.set("PlaySound SELECTION_1.WAV")
				#outmessage.ready.set(1)
				solarSystem.planetEncountered(self.sIndex)




class Initializer(Dependent(SFBool)):
	def evaluate(self,input):
		global display
		global outmessage
		global solarSystem

		if input.get():
			#print "Input get ", display
			#.children.get()
			for x in display.children.get():
				print x
				messagenode.getMessageNode(x)
				outmessage=messagenode.outmessage
				solarSystem = SolarSystem()
				#outmessage.ready.set(0)
				#print outmessage

timer,sunMagnet,mercuryMagnet,venusMagnet,earthMagnet,marsMagnet,jupiterMagnet,saturnMagnet,uranusMagnet,neptuneMagnet,plutoMagnet, bumpButton = references

mercuryButton = ButtonTool(21,mercuryMagnet)
venusButton = ButtonTool(22,venusMagnet)
earthButton = ButtonTool(23,earthMagnet)
marsButton = ButtonTool(24,marsMagnet)
jupiterButton = ButtonTool(25,jupiterMagnet)
saturnButton = ButtonTool(26,saturnMagnet)
uranusButton = ButtonTool(27,uranusMagnet)
neptuneButton = ButtonTool(28,neptuneMagnet)
plutoButton = ButtonTool(29,plutoMagnet)
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

#Keyboard.characters.route( mSelect)

initializer = Initializer()


