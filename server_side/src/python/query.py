#!/usr/bin/env python

import boto3
from boto3.dynamodb.conditions import Key
import json
import datetime
import os.path
import time

# Remember to set AWS_ACCESS_KEY_ID and AWS_SECRET_ACCESS_KEY in
# the environment before running this program.

AWS_REGION = 'us-east-1'
db = boto3.resource('dynamodb', region_name = AWS_REGION)
table = db.Table('2014')

import itertools

# Function adapted from http://code.activestate.com/recipes/577916-fast-minmax-function/
def minmax(data):
    'Computes the minimum and maximum values in one-pass using only 1.5*len(data) comparisons'
    it = iter(data)
    try:
        lo = hi = next(it)
    except StopIteration:
        raise ValueError('minmax() arg is an empty sequence')
    for x, y in itertools.izip_longest(it, it, fillvalue=lo):
        if x > y:
            x, y = y, x
        if x < lo:
            lo = x
        if y > hi:
            hi = y
    return lo, hi



def getTicker(ticker,date):
    data = table.query(KeyConditionExpression = 
                       Key('Ticker').eq(ticker) & 
                       Key('Date').eq(date))
    #print len(data['Items'])
    return_value = "Not found"
    if len(data['Items']) > 0:
        return_value = int(data['Items'][0]['Value'])
    else:
        return -1
    previousDate = datetime.datetime.strptime(date,'%Y-%m-%d') - datetime.timedelta(days=75)
    previousDate = "%04d-%02d-%02d"%(previousDate.year,previousDate.month,previousDate.day)

    data = table.query(KeyConditionExpression = 
                       Key('Ticker').eq(ticker) & 
                       Key('Date').between(previousDate,date))

    values = []
    for l in data['Items']:
        values.append(l['Value'])
        #print "%s ; %d"%(str(l['Date']),l['Value'])

    min,max = minmax(values)

    if return_value > 0:
        if max > 0:
            return_value = int((5*return_value)/max)+1
        else:
            return_value = 5
    elif return_value < 0:
        if min < 0:
            return_value = int((-5*return_value)/min)-1
        else:
            return_value = -5

    if return_value > 5:
        return_value = 5
    elif return_value < -5:
        return_value = -5
    
    return return_value+5

def getTickerDict(name,ticker,date):
    d = dict()
    d['identifier'] = name
    d['value'] = getTicker(ticker,date)
    return d


def getNextDate():
    datefile = "/tmp/datefile"
    date = datetime.datetime(2014,3,1,0,0,0)
    if os.path.isfile(datefile):
        with open (datefile, "r") as text_file:
            datestring=text_file.read().replace('\n', '')
            # print "-----"
            # print datestring
            date = datetime.datetime.strptime(datestring,'%Y-%m-%d %H:%M:%S')
            date += datetime.timedelta(days=1)
            #date = datetime.date(date.year,date.month,date.day) + datetime.timedelta(days=1)
            if date.year == 2015:
                date = datetime.datetime(2014,3,1,0,0,0)
    
    with open(datefile, "w") as text_file:
        text_file.write(str(date))
                
    return date

date = getNextDate()
date = "%04d-%02d-%02d"%(date.year,date.month,date.day)

#date = '2014-10-01'
stocks = list()
stocks.append(getTickerDict('NASAAC','LMEXNA Index',date))
stocks.append(getTickerDict('Aluminium','LMEXAH Index',date))
stocks.append(getTickerDict('Aluminium Alloy','LMEXAA Index',date))
stocks.append(getTickerDict('Steel','LMEXFM Index',date))
stocks.append(getTickerDict('Lead','LMEXPB Index',date))
stocks.append(getTickerDict('Zinc','LMEXZS Index',date))
stocks.append(getTickerDict('Copper','LMEXCA Index',date))
stocks.append(getTickerDict('Tin','LMEXSN Index',date))
stocks.append(getTickerDict('Nickel','LMEXNI Index',date))

#print date
print "{ \"Data\" : %s }"%json.dumps(stocks)

# data = table.query(KeyConditionExpression = 
#                    Key('Ticker').eq('LMEXNA Index') & )
# for l in data['Items']:
#     print "%s ; %d"%(str(l['Date']),l['Value'])


# {u'Type': u'Indicator', u'Ticker': u'LMEXNA Index', u'Description': u'LME Primary NASAAC Stocks', u'Fields': {u'Value': {u'Units': u'metric tonne', u'Frequency': u'Daily'}}}
# {u'Type': u'Indicator', u'Ticker': u'LMEXAH Index', u'Description': u'LME Primary Aluminium Stocks Weekly Change', u'Fields': {u'Value': {u'Units': u'metric tonne', u'Frequency': u'Daily'}}}
# {u'Type': u'Indicator', u'Ticker': u'LMEXAA Index', u'Description': u'LME Aluminium Alloy Stocks', u'Fields': {u'Value': {u'Units': u'metric tonne', u'Frequency': u'Daily'}}}
# {u'Type': u'Indicator', u'Ticker': u'LMEXFM Index', u'Description': u'LME Steel Billet Stocks', u'Fields': {u'Value': {u'Units': u'metric tonne', u'Frequency': u'Daily'}}}
# {u'Type': u'Indicator', u'Ticker': u'LMEXPB Index', u'Description': u'LME Lead Stocks', u'Fields': {u'Value': {u'Units': u'metric tonne', u'Frequency': u'Daily'}}}
# {u'Type': u'Indicator', u'Ticker': u'LMEXZS Index', u'Description': u'LME Zinc Stocks', u'Fields': {u'Value': {u'Units': u'metric tonne', u'Frequency': u'Daily'}}}
# {u'Type': u'Indicator', u'Ticker': u'LMEXCA Index', u'Description': u'LME Copper Stocks', u'Fields': {u'Value': {u'Units': u'metric tonne', u'Frequency': u'Daily'}}}
# {u'Type': u'Indicator', u'Ticker': u'LMEXSN Index', u'Description': u'LME Tin Stocks', u'Fields': {u'Value': {u'Units': u'metric tonne', u'Frequency': u'Daily'}}}
# {u'Type': u'Indicator', u'Ticker': u'LMEXNI Index', u'Description': u'LME Nickel Stocks', u'Fields': {u'Value': {u'Units': u'metric tonne', u'Frequency': u'Daily'}}}


# for el in data['Items']:
#     print "=====" 
#     print el
#     d = dict()
#     #print json.dumps(el)
#     for l in el:
#         print l
#         print el[l]
#         d[str(l)] = str(el[l])
#         #print json.dumps(l)
#     print d
#     print json.dumps(d)
# #print data['Items']
# #print json.dumps(data['Items'])

# table = db.Table('Catalog')
# #data = table.query(KeyConditionExpression = Key('Ticker').eq('UKRPI Index') & Key('Date').between('2012-01-01', '2012-06-30'))
# #data = table.query(KeyConditionExpression = 'Index' in Key('Ticker'))
# data = table.scan()
# for el in data['Items']:
#     if el['
#     print el

