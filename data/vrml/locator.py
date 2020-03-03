display = getDisplay()

class Locator(Dependent(SFVec3f)):
    def __init__(self):
        SFVec3f.__init__(self)
    def evaluate(self, ina):
        #in_vec=in_vec.get()
        ina=ina.get()
        print str(ina.x) + " " + str(ina.y) + " " + str(ina.z)
        #return in_vec.get()

class Locator2(Dependent(SFVec3f)):
    def evaluate(self, in_vec):
        #in_vec=in_vec.get()
        #print in_vec
        return in_vec.get()

class Foo(Dependent(SFVec3f)):
    def evaluate(self, ina):
        print ina.get()

coordLocator = Locator2()
coordPrinter = Locator()
#printer = Foo()
di=getDeviceInfoTop()
di= di.devices.get()[0]
di.position.route(coordLocator)
#references[0].coordLocator.route(printer)
#print "a"
#coordLocator.route(printer)
#print "b"
