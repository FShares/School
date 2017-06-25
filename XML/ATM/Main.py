#!/usr/bin/python
# -*- coding=utf-8 -*-
'''
导入method下的方法
'''
from Method import MyXML as X
from Method import switch as Switch         # Python -->switch case(自己实现的,无现成方法)
from Method import Bank as Bank             # Python --> 业务逻辑方法

def register():
    Uname = input("请输入账户名：")
    Upass = input("请输入账户密码：")
    Upass2 = input("输再次输入账户密码：")
    # 判断两次密码是否匹配
    while (Upass != Upass2):
        print("两次密码不匹配！")
        print("请重新输入密码：")
        Upass = input("请输入账户密码：")
        Upass2 = input("输再次输入账户密码：")
    URname = input("请输入户主姓名：")
    USex = input("请输入性别：")
    X.addUser(Uname,Upass,URname,USex)                   #通过MyXML添加方法实现

def login():
    ID = input("请输入用户名：")
    if (Bank.queryAccount(ID) == None):
        print("您输入的账户不存在,请先注册。")
        return
    password = input("请输入银行密码：")
    result = Bank.verifyAccount(ID,password)
    Rname = Bank.queryAccount(ID)
    #print(result==None)
    if(result.Account.uBalance!=""):
        print("您好  "+Rname+" ， 登录成功！")
        ID = result.Account.uname
        while True:
            print("******欢迎使用XXX银行模拟ATM系统，请按如下步骤操作******")
            print("           *1.查询账户余额")
            print("           *2.存款")
            print("           *3.取款")
            print("           *4.转账")
            print("           *5.改密")
            print("           *6.退卡")
            flag = input("请输入：")
            for case in Switch.switch(flag):
                if case('1'):                               # 查询账户余额
                    print("您的账户还有" +Bank.queryBalance(ID)+"元钱")
                    break
                if case('2'):                                # 存款
                    money = input("请输入您的存款金额：")
                    if int(money) % 100 != 0:
                        print("存款额度必须为100的整数")
                        continue
                    if int(money) > 2000:
                        print("每次存款必须小于2000人民币")
                        continue
                    Bank.deposit(money)
                    print("您的账户还有" +Bank.queryBalance(ID)+"元钱")
                    break
                if case('3'):                              # 取款
                    money = input("请输入您的取款金额：")
                    if int(money) % 100 != 0:
                        print("取款额度必须为100的整数")
                        continue
                    if int(money) > 2000:
                        print("每次取款必须小于2000人民币")
                        continue
                    oldMoney = Bank.queryBalance(result.Account.uname)
                    if int(money) > int(oldMoney):
                        print("您账户余额不足")
                        continue
                    Bank.withdraw(money)
                    print("您的账户还有" +Bank.queryBalance(ID)+"元钱")
                    break
                if case('4'):                   # 转账
                    a = input("请输入需要转的账号:")
                    if(Bank.queryAccount(a)==None):
                        print("您输入的账户不存在")
                        continue
                    money = input("请输入您的转账金额：")
                    if int(money) % 100 != 0:
                        print("转账额度必须为100的整数")
                        continue
                    if int(money) > 2000:
                        print("转账金额必须小于2000人民币")
                        continue
                    Bank.transferom(a,money)
                    print("您的账户还有" +Bank.queryBalance(ID)+"元钱")
                    break
                if case('5'):                   # 修改密码
                    # 判断两次密码是否匹配7
                    Upass = input("请输入账户密码：")
                    if(Bank.queryPWD(ID)==None):
                        print("您输入的密码不正确")
                        continue
                    Upass2 = input("请输入新密码:")
                    Upass3 = input("输再次输入账户密码：")
                    if(Upass3 != Upass2):
                        print("两次输入的密码不一致")
                        continue
                    Bank.modifyPWD(Upass2)
                    break
                if case('6'):                   # 退出
                    break
                if case():  # default, could also just omit condition or 'if True'
                    print("选择输入不合法，请重新选择!")
                    # No need to break here, it'll stop anyway
    else:
        print("密码不正确")
'''
这是主方法
'''
if __name__ == "__main__":
    while True:
        print("******欢迎使用XXX银行模拟ATM系统，请按如下步骤操作******")
        print("    *1.用已有账户登录")
        print("    *2.没有账户，开户")
        print("    *3.所有账户统计")
        print("    *4.退出")
        flag = input("请输入：")
        # The following example is pretty much the exact use-case of a dictionary,
        # but is included for its simplicity. Note that you can include statements
        # in each suite.
        for case in Switch.switch(flag):
            if case('1'):
                login()                     # 登录
                break
            if case('2'):
                register(),                 # 注册
                break
            if case('3'):
                Bank.allAccount(),           # 统计
                break
            if case('4'):                   # exit
                exit()
                break
            if case():  # default, could also just omit condition or 'if True'
                print("选择输入不合法，请重新选择!")
                # No need to break here, it'll stop anyway