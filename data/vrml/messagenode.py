print "messagenode"
outmessage=None
#inmessage=None 

def getMessageNode(node):
    print "getmessagenode:" + str(node.name())

    global outmessage
    #global inmessage
    if(node.name()=="Group" or node.name()=="Transform"):
		pass
		#for x in node.children.get():
		#	getMessageNode(x)
    elif(node.name()=="SimpleMsgNode"):
		print "found SimpleMsgNode"
		#if(not node.inbound.get()):
		#	print "Gotcha!!!"
		outmessage=node
	#else:
	#	inmessage=node



