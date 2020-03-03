import Insert3DConnexionDevice
mg = Insert3DConnexionDevice.insert()

import messagenode
global outmessage
outmessage = messagenode.outmessage

#########################################
#
# Listens the magellans "joystick" if its pushed.
# Sends agent message when triggered.
#
#########################################
class poop:
	def kakka(self):
		print "pokale"

class MagellanAsButton (Dependent(SFVec3f)):
  def __init__(self):
    SFVec3f.__init__(self)
    self.prev = 0

  def evaluate(self, input):
    global outmessage
    coords = str(input.get())
    temp, x, y, z, temp2 = coords.split()
#    print z
    if(float(z) < -0.0035):
      push = 1
    else:
      push = 0

#    print push, self.prev
    if (push != self.prev and push == 1):
      om = "IN SA : cmd=back;"
      print om
      outmessage.content.set(om)
      outmessage.ready.set(1)
#    else:
#      control.magellanRelease()

    self.prev = push

mgAsButton = MagellanAsButton()
mg.instantTranslation.route(mgAsButton)

