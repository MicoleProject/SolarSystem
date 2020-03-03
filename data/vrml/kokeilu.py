print "loading kokeilu.py"
from math import *
from time import time
#from pythonscript import *
display = getDisplay()

class OrbitTool(Dependent (SFTime)):
	def __init__(self, x, y, scale, sIndex):
		SFTime.__init__(self)
		#SFVec3f.__init__(self)
		self.x = pow(x*scale,2)
		self.y = pow(y*scale,2)
		self.sIndex = sIndex
	def evaluate(self, input):
		global aKunta
		#print "orbitTool"
		xPos = display.trackerPosition.get().x
		yPos = display.trackerPosition.get().y
		zPos = display.trackerPosition.get().z
		a = pow(xPos,2)/self.x + pow(yPos,2)/self.y
		if 0.95 < a and a < 1.05 and zPos < 0.02:
			print "if", self.sIndex
			#aKunta.orbitEntered(self.sIndex)

class MagnetTool(Dependent(SFBool)):
	def __init__(self,sIndex=0):
		SFBool.__init__(self)
		self.sIndex = sIndex
	def evaluate(self,input):
		#global aKunta
		print "magnettool", str(input.get())
		if input.get():
			print "pof:", str(self.sIndex)
			#aKunta.planetEncountered(self.sIndex)

class ButtonTool ( Dependent(SFBool)):
	def __init__ (self, sIndex, planetMagnet):
		SFBool.__init__(self)
		self.sIndex = sIndex
		self.planet = planetMagnet

	def evaluate(self, input):
		print "buttontool", input
		#global player
		if input.get():
			if self.planet.grasping.get():
				#player.playBackgroundSound('VALINTA_1')
				#aKunta.planetEncountered(self.sIndex)
				print "Button tool: ", self.sIndex
 

timer,sunMagnet,mercuryMagnet,venusMagnet,earthMagnet,marsMagnet,jupiterMagnet,saturnMagnet,uranusMagnet,neptuneMagnet,plutoMagnet, bumpButton = references

#aKunta = Aurinkokunta()
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
timer.cycleTime.route(mercuryOrbit)
timer.cycleTime.route(venusOrbit)
timer.cycleTime.route(earthOrbit)
timer.cycleTime.route(marsOrbit)
timer.cycleTime.route(jupiterOrbit)
timer.cycleTime.route(saturnOrbit)
timer.cycleTime.route(uranusOrbit)
timer.cycleTime.route(neptuneOrbit)
timer.cycleTime.route(plutoOrbit)

