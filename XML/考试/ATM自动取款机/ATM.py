#!/usr/bin/env python
#coding=utf8
# tab completion
import readline
readline.parse_and_bind('tab: complete')
# history file
import os
histfile = os.path.join(os.environ['HOME'], '.pythonhistory')

import fileinput
import time
import pickle

Bill = {}
products = {}
shopList = []

def Bill(Account,Time,Description,RMB):
    Bill = {"Account":Account,"Time":Time,"Description":Description,"RMB":RMB}
    pickle.dump(Bill,open("bill","a"))

def shop():
    print "\n\033[;32mWelcome to coral mall, only you think, no you can't buy\033[0m"
    for line in fileinput.input("shops"):
        print "\t%s" % line.strip()
    while True:
        for f in fileinput.input("shops"):
            list1 = f.split()[0]
            list2 = f.split()[1]
            products[list1] = list2

        choices = raw_input("Please enter the purchase of products or back (b): ").strip()
        if len(choices) == 0:continue
        elif choices == 'b' or choices == 'back':list()
        
        if products.has_key(choices):
            balance = pickle.load(open("userinfo","r"))
            if int(products[choices]) > balance[accountAuth][2]:
                print "\033[;31mYour balance is insufficient\033[0m"
            else:
                while True:
                    shopList.append(choices)
                    new_balance = int(balance[accountAuth][2]) - int(products[choices])
                    userInfo[accountAuth][2] = int(new_balance)
                    pickle.dump(userInfo,open("userinfo","wb"))

                    Bill(accountAuth,time.strftime("%Y-%m-%d %H:%M:%S"),choices,"-%d" % int(products[choices]))

                    print "\033[;32mConsumption is %r Money is %r\033[0m" % (products[choices],new_balance)
                    print "\033[;33mThe shopping list %s \033[0m" % shopList
                    break
        else:
            print "\033[;31mYou choose %r not in the list\033[0m" % choices
            shop()

def queryMoney():
    userInfo = pickle.load(open("userinfo","rb"))
    credit = userInfo[accountAuth][1]
    balance = userInfo[accountAuth][2]
    print "\033[;32mYour limit money is %r yuan, Your balance is %r yuan\033[0m" % (credit,balance)

def saveMoney():
    while True:
        desc = raw_input("Please describe save money: ").strip()
        if len(desc) == 0:continue
        
        try:
            input = int(raw_input("Please enter the store number of money: "))
        except ValueError:
            print "\033[;31mYou entered must be number\033[0m"
            saveMoney()
        
        if input % 100 != 0:
            print "\033[;31mDeposit amount must be 100 integer times\033[0m"
            continue
        if input > 2000:
            print "\033[;31mDeposit the maximum amount of 2000 yuan\033[0m"
            continue
        userInfo = pickle.load(open("userinfo","rb"))
        new_balance = int(userInfo[accountAuth][2]) + input
        userInfo[accountAuth][2] = int(new_balance)
        pickle.dump(userInfo,open("userinfo","wb"))
        print "\033[;32mYour credit is %r,Your balance is %r\033[0m" % (userInfo[accountAuth][1],userInfo[accountAuth][2])

        Bill(accountAuth,time.strftime("%Y-%m-%d %H:%M:%S"),desc,"+%d" % float(input))
        
        explain = raw_input("continue ('c'),return ('b'),quit ('q')")
        if explain == 'c':continue
        elif explain == 'b':list()
        else:exit()

def drawMoney():
    while True:
        desc = raw_input("Please describe draw money: ").strip()
        if len(desc) == 0:continue
        
        try:
            input = int(raw_input("Please enter the store number of money: "))
        except ValueError:
            print "\033[;31mYou entered must be number\033[0m"
            drawMoney()
        
        if input % 100 != 0:
            print "\033[;31mDeposit amount must be 100 integer times\033[0m"
            continue
        if input > 2000:
            print "\033[;31mWithdrawal limit of up to 2000 yuan\033[0m"
            continue
        balance = pickle.load(open("userinfo","rb"))
        if input > int(balance[accountAuth][2]):
            print "\033[;31mYour balance is insufficient\033[0m"
            list()
        userInfo = pickle.load(open("userinfo","rb"))
        new_balance = int(userInfo[accountAuth][2]) - input - input * 0.05
        userInfo[accountAuth][2] = int(new_balance)
        pickle.dump(userInfo,open("userinfo","wb"))
        print "\033[;32mYour credit is %r,Your balance is %r\033[0m" % (userInfo[accountAuth][1],userInfo[accountAuth][2])

        Bill(accountAuth,time.strftime("%Y-%m-%d %H:%M:%S"),desc,"-%d" % float(input))
        
        explain = raw_input("continue ('c'),return ('b'),quit ('q')")
        if explain == 'c':continue
        elif explain == 'b':list()
        else:exit()

def transferMoney():
    while True:
        userInfo = pickle.load(open("userinfo","rb"))
        desc = raw_input("Please describe draw money: ").strip()
        if len(desc) == 0:continue
        d_account = raw_input("Please input transfer account: ").strip()
        if len(d_account) == 0:continue
        if userInfo.has_key(d_account) is False:
            print "\033[;31mThis account does not exist\033[0m"
            transferMoney()
        d_money = int(raw_input("Please input transfer amount money: "))
        if d_money % 100 != 0:
            print "\033[;31mDeposit amount must be 100 integer times\033[0m"
            continue
        if d_money > 2000:
            print "\033[;31mWithdrawal limit of up to 2000 yuan\033[0m"
            continue
        if d_money > int(userInfo[accountAuth][2]):
            print "\033[;31mYour balance is insufficient\033[0m"
            continue
        userInfo[accountAuth][2] = int(userInfo[accountAuth][2]) - d_money - d_money * 0.10
        userInfo[d_account][2] = int(userInfo[d_account][2]) + d_money
        pickle.dump(userInfo,open("userinfo","wb"))
        print "\033[;32mYour credit is %r,Your balance is %r\033[0m" % (userInfo[accountAuth][1],userInfo[accountAuth][2])

        Bill(accountAuth,time.strftime("%Y-%m-%d %H:%M:%S"),desc,"-%d" % (userInfo[accountAuth][2] - d_money - d_money * 0.10))
        
        explain = raw_input("continue ('c'),return ('b'),quit ('q')")
        if explain == 'c':continue
        elif explain == 'b':list()
        else:exit()



def queryBill():
    Income = []
    Spending = []
    num = 0
    print "Account\t\tTime\t\tDescription\t\tRMB"
    f = open("bill","r")
    while True:
        try:
            line = pickle.load(f)
            #if len(line) == 0:continue
            if line["Account"] == accountAuth:
                if '+' in line["RMB"]:
                    print "\033[;33m%r\t%r\t%r\t\t\t%r\033[0m" % (line["Account"],line["Time"],line["Description"],line["RMB"])
                    income = line["RMB"].strip("+")
                    Income.append(income)
                else:
                    print "%r\t%r\t%r\t\t\t%r" % (line["Account"],line["Time"],line["Description"],line["RMB"])
                    spending = line["RMB"].strip("-")
                    Spending.append(spending)
        except:
            break
    for i in Income:
        num = num + int(i)
    income = num
    print "Income is %r" % num
    for i in Spending:
        num = num + int(i)
    spending = num
    print "Spending is %r" % num
    print "Total is %r" % (int(income) + int(spending))

def modifyPass():
    userInfo = pickle.load(open("userinfo","rb"))
    old_pass = raw_input("Please input old passwd: ").strip()
    while True:
        if old_pass == userInfo[accountAuth][0]:
            new_pass1 = raw_input("Please input new passwd: ").strip()
            if len(new_pass1) < 3:
                print "\033[;31mPassword length must be more than 3\033[0m"
                continue
            new_pass2 = raw_input("Please input new passwd again: ").strip()
            if new_pass1 != new_pass2:
                print "\033[;31mTwo passwords are not identical\033[0m"
            else:
                userInfo[accountAuth][0] = new_pass2
                pickle.dump(userInfo,open("userinfo","wb"))
                print "\033[;32mPassword change is successful, please login again\033[0m"
                exit()
        else:
            print "\033[;31mold password input error\033[0m"
            modifyPass()

def list():
    print """\033[;32mWelcome to use 珊瑚银行 AMT automatic teller machine
            If the machine failure please contact 珊瑚\thot line:110\033[0m\n"""
    print "\t(1) shop"
    print "\t(2) query money"
    print "\t(3) save money"
    print "\t(4) draw money"
    print "\t(5) transfer money"
    print "\t(6) query bill"
    print "\t(7) modify pass"
    print "\t(8) quit"
    while True:
        choices = raw_input("Please choices:").strip()
        if len(choices) == 0:continue
        if choices == '1':shop()
        elif choices == '2':queryMoney()
        elif choices == '3':saveMoney()
        elif choices == '4':drawMoney()
        elif choices == '5':transferMoney()
        elif choices == '6':queryBill()
        elif choices == '7':modifyPass()
        else:
            print "\033[;31mPlease pay attention to the property security\033[0m"
            exit()

#pickle.dump(userInfo,open("userinfo","wb"))
#userInfo = {'111':['123','15000','15000'],
#               '222':['456','8000','8000'],
#               '333':['789','3000','3000']
#            }
#pickle.dump(userInfo,open("userinfo","rb+"))

userInfo = pickle.load(open("userinfo","rb"))
while True:
    accountAuth = raw_input("Please input user \033[;34maccount\033[0m:").strip()
    if len(accountAuth) == 0:continue
    if userInfo.has_key(accountAuth):
        if 'lock' in userInfo[accountAuth]:
            print "%r user has been locked, please unlock" % accountAuth
            exit()
        for num in range(3,0,-1):
            passwdAuth = raw_input("Please input user \033[;34mpassword\033[0m:").strip()
            if len(passwdAuth) == 0:continue
            if passwdAuth == userInfo[accountAuth][0]:
                list()
            else:
                print "Wrong password, Can try again %r itmes" % num
                continue
        else:
                lockaccount = userInfo[accountAuth]
                lockaccount.append("lock")
                pickle.dump(userInfo,open("userinfo","wb"))
                print "\033[;31mAccount freeze within 24 hours\033[0m"
                exit()
    else:
        print "\033[;31mWrong account %r,retype\033[0m" % accountAuth
