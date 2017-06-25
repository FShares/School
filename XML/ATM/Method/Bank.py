# -*- coding=utf-8 -*-
import  xml.dom.minidom
from Method import MyXML as X
from Method import Accounts

#验证用户登录信息是否匹配
def  verifyAccount(ID, password):
    # 打开xml文档
    dom = xml.dom.minidom.parse('./user.xml')
    # 得到文档元素对象
    root = dom.documentElement
    itemlist = root.getElementsByTagName('userinfo')
    Account = Accounts
    Account.Account.uname = ID
    Account.Account.uPass = password
    #获得userinfo的属性
    for i in itemlist:
        #验证用户和密码是否匹配
        if(ID==i.getAttribute("id")):
            if(password==i.getAttribute("uPass")):
                Account.Account.uBalance = i.getAttribute("balance")
                Account.Account.uSex = i.getAttribute("uSex")
                Account.Account.uRname = i.firstChild.data
                #print("密码匹配")
                break
    return Account

'''
查询用户真实的姓名
'''
def queryAccount(ID):
    result = ""
    # 打开xml文档
    dom = xml.dom.minidom.parse('./user.xml')
    # 得到文档元素对象
    root = dom.documentElement
    itemlist = root.getElementsByTagName('userinfo')
    for i in itemlist:
        #验证用户和密码是否匹配
        if(ID==i.getAttribute("id")):
            return i.firstChild.data
'''
查询用户余额
'''
def queryBalance(ID):
    result = ""
    # 打开xml文档
    dom = xml.dom.minidom.parse('./user.xml')
    # 得到文档元素对象
    root = dom.documentElement
    itemlist = root.getElementsByTagName('userinfo')
    for i in itemlist:
        #验证用户和密码是否匹配
        if(ID==i.getAttribute("id")):
            return i.getAttribute("balance")

'''
查询用户密码
'''
def queryPWD(ID):
    result = ""
    # 打开xml文档
    dom = xml.dom.minidom.parse('./user.xml')
    # 得到文档元素对象
    root = dom.documentElement
    itemlist = root.getElementsByTagName('userinfo')
    for i in itemlist:
        #验证用户和密码是否匹配
        if(ID==i.getAttribute("id")):
            return i.getAttribute("uPass")
'''
存款
'''
def deposit(money1):
    account = Accounts
    b = int(queryBalance(account.Account.uname))
    b += int(money1)
    ID = account.Account.uname
    # 1. 读取xml文件
    tree = X.read_xml("./user.xml")
    # 2. 属性修改
    # A. 找到父节点
    nodes = X.find_nodes(tree, "list/userinfo")
    # B. 通过属性准确定位子节点
    result_nodes = X.get_node_by_keyvalue(nodes, {"id": ID})
    # C. 修改节点属性
    X.change_node_properties(result_nodes, {"balance": str(b)})
    # 输出到结果文件
    X.write_xml(tree, "./user.xml")

'''
取款
'''
def withdraw(money1):
    account = Accounts
    b = int(queryBalance(account.Account.uname))
    b -= int(money1)
    ID = account.Account.uname
    # 1. 读取xml文件
    tree = X.read_xml("./user.xml")
    # 2. 属性修改
    # A. 找到父节点
    nodes = X.find_nodes(tree, "list/userinfo")
    # B. 通过属性准确定位子节点
    result_nodes = X.get_node_by_keyvalue(nodes, {"id": ID})
    # C. 修改节点属性
    X.change_node_properties(result_nodes, {"balance": str(b)})
    # 输出到结果文件
    X.write_xml(tree, "./user.xml")

'''
转账
'''
def transferom(account2,moeny):
    account = Accounts
    ID = account.Account.uname
    b = int(queryBalance(ID))
    b -= int(moeny)
    c = int(queryBalance(account2))
    c += int(moeny)
    # 1. 读取xml文件
    tree = X.read_xml("./user.xml")
    # 2. 属性修改
    # A. 找到父节点
    nodes = X.find_nodes(tree, "list/userinfo")
    # B. 通过属性准确定位子节点
    result_nodes = X.get_node_by_keyvalue(nodes, {"id": ID})
    # C. 修改节点属性
    X.change_node_properties(result_nodes, {"balance": str(b)})
    result_nodes = X.get_node_by_keyvalue(nodes, {"id": account2})
    X.change_node_properties(result_nodes, {"balance": str(c)})
    # 输出到结果文件
    X.write_xml(tree, "./user.xml")

'''
改密
'''
def modifyPWD(Upass):
    account = Accounts
    ID = account.Account.uname
    # 1. 读取xml文件
    tree = X.read_xml("./user.xml")
    # 2. 属性修改
    # A. 找到父节点
    nodes = X.find_nodes(tree, "list/userinfo")
    # B. 通过属性准确定位子节点
    result_nodes = X.get_node_by_keyvalue(nodes, {"id": ID})
    # C. 修改节点属性
    X.change_node_properties(result_nodes, {"uPass": Upass})
    # 输出到结果文件
    X.write_xml(tree, "./user.xml")

'''
统计银行所有用户信息
'''
def allAccount():
    # 打开xml文档
    dom = xml.dom.minidom.parse('./user.xml')
    # 得到文档元素对象
    root = dom.documentElement
    itemlist = root.getElementsByTagName('userinfo')
    #获得userinfo的属性
    print("统计信息如下：")
    print("name,\tid,\tsex,\tbalance")
    for i in itemlist:
        print(i.firstChild.data + "\t"+ i.getAttribute("id")+ "\t" + i.getAttribute("Usex")+"\t\t"+i.getAttribute("balance"))
#<userinfo Usex="男" balance="500.0" id="1" uPass="1">刘邦龙</userinfo>