print "loading earth.py"
sys.path.append("./")
#sys.path.append("C:/rami/micole_cvs/micole/solarsystem/data/vrml")
sys.path.append("C:/jouni/micole/solarsystem/data/vrml")

#sys.path.append("../../vrml")
#import sourcefinder
import Keyboard
import Insert3DConnexionDevice
import messagenode
import time
#---------------------------------------------------------
#import threading
#lukko=threading.Lock()
#---------------------------------------------------------

#import sourcefinder_nu
rotator = None
hd = None
finalizer = None
initializer = None
afrikka = None
eurooppa = None
pNapa = None
eNapa = None
australia = None
atlantti1 = None
atlantti2 = None
tyyni1 = None
tyyni2 = None

initialized = None
print "xx"

scene,maaTransform,afrikkaMagneetti,tyyni1Magneetti,tyyni2Magneetti,atl1Magneetti,atl2Magneetti,eurooppaMagneetti,pNapaMagneetti,eNapaMagneetti,australiaMagneetti,aasiaMagneetti,pAmerikkaMagneetti,eAmerikkaMagneetti,gravMagnet,gravInterpolator,suomiMagneetti, kuuMagneetti = references
#scene,maaTransform,afrikkaMagneetti,tyyni1Magneetti,tyyni2Magneetti,atl1Magneetti,atl2Magneetti,eurooppaMagneetti,pNapaMagneetti,eNapaMagneetti,australiaMagneetti,gravMagnet,gravInterpolator,suomiMagneetti = references
print "xx"

#for x in getDisplay().children.get():
#    sourcefinder_nu.getSoundNodes(x)

for x in getDisplay().children.get():
    #print str(x) + " :: "
    messagenode.getMessageNode(x)

global outmessage
outmessage=messagenode.outmessage


#---------------------------------------------------------

#class MaaLahelta(SoundPlayer):
#    def __init__(self):
#        global player
#        player.addSound('AFRIKKA', "../../wav/maan_pinnan_yleinen.wav")
#        player.addSound('EUROOPPA', "../../wav/maan_pinnan_yleinen.wav")
#        player.addSound('PAMERIKKA', "../../wav/maan_pinnan_yleinen.wav")
#        player.addSound('EAMERIKKA', "../../wav/maan_pinnan_yleinen.wav")
#        player.addSound('AUSTRALIA', "../../wav/maan_pinnan_yleinen.wav")
#        player.addSound('PTASAAJA', "../../wav/maan_pinnan_yleinen.wav")
#        player.addSound('PNAPA', "../../wav/maan_pinnan_yleinen.wav")
#        player.addSound('ENAPA', "../../wav/maan_pinnan_yleinen.wav")
#        player.addSound('TYYNIMERI', "../../wav/pilotti1meribounce.wav")
#        player.addSound('ATLANTTI', "../../wav/pilotti1meribounce.wav")
#        player.addSound('KELLO', "../../wav/kellontikitys.wav")
#        player.addSound('TERVETULOA', "../../wav/ML_tervetuloa.wav")
#        player.addSound('SUOMI', "../../wav/suomi.wav")
#        print "MaaLahelta __init__() kayty"
#
#    def rotationStarted(self):
#        player.playLoopSound('KELLO')
#
#    def rotationEnded(self):
#        player.stopSound('KELLO')
#
#    def changeSounds(self):
#        print "*"
#        global player
#        player.changeSound('AFRIKKA', "../../wav/maajattilainen12.wav")
#        player.changeSound('EUROOPPA', "../../wav/maajattilainen11.wav")
#        player.changeSound('PAMERIKKA', "../../wav/maajattilainen14.wav")
#        player.changeSound('EAMERIKKA', "../../wav/maajattilainen13.wav")
#        player.changeSound('AUSTRALIA', "../../wav/maajattilainen15.wav")
#        player.changeSound('PTASAAJA', "../../wav/paivantasaaja.wav")
#        player.changeSound('PNAPA', "../../wav/maajattilainen21.wav")
#        player.changeSound('ENAPA', "../../wav/maajattilainen22.wav")
#        player.changeSound('TYYNIMERI', "../../wav/maajattilainen17.wav")
#        player.changeSound('ATLANTTI', "../../wav/maajattilainen18.wav")


class Rotator (Dependent (SFVec3f)):
    def __init__(self, step, limit):
        SFVec3f.__init__(self)
        self.step = step
        self.limit = limit
        self.yRot = 0.0
        self.rotation = 0

    def evaluate(self, vecIn):
        #print "Evaluating device position"
        #print references[0].rotation.get()
        xPos = vecIn.get().x

        if(xPos > self.limit):
            #print "Rotating the globe",maaTransform.rotation.get(),self.yRot
            self.yRot += self.step
            maaTransform.rotation.set(Rotation(Vec3f(0,1,0),self.yRot))

            if not self.rotation:
                self.rotation = 1
        else:
            if self.rotation:
                self.rotation = 0




class Pyorittaja ( Dependent (SFFloat)):

	#Tähän sitten joskus kekseliäs konfigurointi, jooko?
	def __init__(self, vas, oik, yla, ala, askel):
		SFFloat.__init__(self)
		self.vasen = vas
		self.oikea = oik
		self.yla = yla
		self.ala = ala
		self.askel = askel
		#self.akseli = Vec3f(0, 0, 0)
		self.xRot = 0.0
		self.yRot = 0.0





	def evaluate ( self, inTime ):
		#print "EVALUATE"


		vector =  getDisplay().trackerPosition.get()

		rotation = references[0].rotation.get()
		#print rotation.axis.x
		#print rotation.axis.y
		#print vector

		if ( vector.x > self.oikea):
			#self.yRot = 0
			self.xRot -= self.askel
			references[0].rotation.set(Rotation(Vec3f(0,1,0), self.xRot))


		elif (vector.x < self.vasen ):
			#self.yRot = 0
			self.xRot += self.askel
			references[0].rotation.set(Rotation(Vec3f(0,1,0), self.xRot))

		if ( vector.y > self.yla):
			#y = 1
			#self.xRot = 0
			self.yRot += self.askel
			references[0].rotation.set(Rotation(Vec3f(1,0,0), self.yRot))

		elif( vector.y < self.ala ):
			#y = 1
			#self.xRot = 0
			self.yRot -= self.askel
			references[0].rotation.set(Rotation(Vec3f(1,0,0), self.yRot))

		#print self.akseli


#pyorittaja = Pyorittaja(-0.05, 0.05, 0.05, -0.05, 0.001)




class Speak(Dependent (SFBool)):
    def __init__(self,comment):
        SFBool.__init__(self)
        self.comment = comment
        print "Speech \""+ self.comment +"\" has been created."

    def evaluate(self,input):
    	global outmessage
        if input.get():
            om = "OUT SPCH : str=" + self.comment + ";priority=false;"
            print om
            outmessage.content.set(om)
            outmessage.ready.set(1)

class DistanceCounter( Dependent ( TypedField( SFFloat, SFVec3f ) ) ):
    def __init__(self):
        SFFloat.__init__(self)

    def evaluate(self, pos):
        self.x = pos[0].get().x
        self.y = pos[0].get().y
        self.z = pos[0].get().z
        self.dist = max(abs(self.x), abs(self.y))
        self.dist = max(abs(self.z), self.dist)
        return self.dist


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
#		print z
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


class Finalizer(Dependent(SFBool)):
    def evaluate(self,input):
        if input.get():
            finalize()


class Initializer(Dependent(SFBool)):
    def evaluate(self,input):
        print "Initialize evaluate"
        if input.get():
            initializem()

def initializem():
    print "Initializing: earth.py"
    #--------------------------------------------
    #agentPlayer= AgentSoundPlayer()
    #agent_sound.buffer.get().url.set("../../wav/silence_1sec.wav")
    #--------------------------------------------
    global rotator
    global hd
    global d
    global afrikka
    global eurooppa
    global pNapa
    global eNapa
    global australia
    global atlantti1
    global atlantti2
    global tyyni1
    global tyyni2
    global suomi
    global kuu
    global aasia
    global eAmerikka
    global pAmerikka
    global initialized
    global initializer
    global finalizer
    global keyboardListener

    global pbl
    global tipColorChanger
    global mgAsButton
    global mgBT
    global mg

    global outmessage

    if initialized is not None and initialized.get()==1:
        return

    distCounter = DistanceCounter()
    display = getDisplay()
    display.trackerPosition.route(distCounter)
    distCounter.route(gravInterpolator.set_fraction)
    gravInterpolator.value_changed.route(gravMagnet.stiffness)

    pbl = PhantomButtonListener()
    display.button.route(pbl)

    tipColorChanger = TipColorChanger()
    scene.hapticForce.route(tipColorChanger)

    mg = Insert3DConnexionDevice.insert()
    mgAsButton = MagellanJoystickAsButton()
    mg.instantTranslation.route(mgAsButton)

    mgBT = MagellanButtonTracker()
    mg.buttons.route(mgBT)


#    maaLahelta = MaaLahelta()
    afrikka = Speak('Afrikka')
    eurooppa = Speak('Eurooppa')
    pNapa = Speak('Pohjoisnapa')
    eNapa = Speak('Etelänapa')
    australia = Speak('Australia')
    atlantti1 = Speak('Pohjoinen Atlantin valtameri')
    atlantti2 = Speak('Eteläinen Atlantin valtameri')
    tyyni1 = Speak('Pohjoinen Tyynivaltameri')
    tyyni2 = Speak('Eteläinen Tyynivaltameri')
    suomi = Speak('Suomi')
    kuu = Speak('Kosketat Kuuta')
    aasia = Speak('Aasia')
    pAmerikka = Speak('Pohjois-Amerikka')
    eAmerikka = Speak('Etelä-Amerikka')
    afrikkaMagneetti.grasping.route(afrikka)
    tyyni1Magneetti.grasping.route(tyyni1)
    tyyni2Magneetti.grasping.route(tyyni2)
    atl1Magneetti.grasping.route(atlantti1)
    atl2Magneetti.grasping.route(atlantti2)
    eurooppaMagneetti.grasping.route(eurooppa)
    pNapaMagneetti.grasping.route(pNapa)
    eNapaMagneetti.grasping.route(eNapa)
    australiaMagneetti.grasping.route(australia)
    suomiMagneetti.grasping.route(suomi)
    kuuMagneetti.grasping.route(kuu)
    aasiaMagneetti.grasping.route(aasia)
    eAmerikkaMagneetti.grasping.route(eAmerikka)
    pAmerikkaMagneetti.grasping.route(pAmerikka)

    print "Magnets routed"

    d = getDeviceInfoTop()
    hd = d.devices.get()[0]
    rotator = Rotator (0.003,0.05)
    hd.position.route(rotator)

    print "rotator routed"

    initializer = Initializer()
    finalizer = Finalizer()
    initialized = SFBool(1)
    print "*** earth.py initialized ***"
    #player.playWav('TERVETULOA',0,1,'no','yes')

def finalize():
    print "Finalizing: earth.py"

    global rotator
    global hd
    global d
 #   global maaLahelta
    global afrikka
    global eurooppa
    global pNapa
    global eNapa
    global australia
    global atlantti1
    global atlantti2
    global tyyni1
    global tyyni2
    global suomi
    global kuu
    global messageListener

    display = getDisplay()

    global pbl
    global tipColorChanger
    global mgAsButton
    global mgBT
    global mg
    display.button.unroute(pbl)
    scene.hapticForce.unroute(tipColorChanger)
    mg.instantTranslation.unroute(mgAsButton)
    mg.buttons.unroute(mgBT)

    print "4"
    hd.position.unroute(rotator)
    #Keyboard.characters.unroute(keyboardListener)
    print "hd unrouted"
    afrikkaMagneetti.grasping.unroute(afrikka)
    tyyni1Magneetti.grasping.unroute(tyyni1)
    tyyni2Magneetti.grasping.unroute(tyyni2)
    atl1Magneetti.grasping.unroute(atlantti1)
    atl2Magneetti.grasping.unroute(atlantti2)
    eurooppaMagneetti.grasping.unroute(eurooppa)
    pNapaMagneetti.grasping.unroute(pNapa)
    eNapaMagneetti.grasping.unroute(eNapa)
    australiaMagneetti.grasping.unroute(australia)
    suomiMagneetti.grasping.unroute(suomi)
    kuuMagneetti.grasping.unroute(kuu)
    aasiaMagneetti.grasping.unroute(aasia)
    eAmerikkaMagneetti.grasping.unroute(eAmerikka)
    pAmerikkaMagneetti.grasping.unroute(pAmerikka)
    print "magnets unrouted"
    initialized = SFBool(0)
    print "Maa-lahelta lopetettu"

#initialize()


initializer = Initializer()
finalizer = Finalizer()
