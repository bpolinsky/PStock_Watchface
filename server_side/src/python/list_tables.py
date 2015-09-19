#!/usr/bin/env python

import boto3
import json

# Remember to set AWS_ACCESS_KEY_ID and AWS_SECRET_ACCESS_KEY in
# the environment before running this program.

AWS_REGION = 'us-east-1'

db = boto3.client('dynamodb',
                  region_name = AWS_REGION)
                    
tables = db.list_tables()
#print tables['TableNames']
print json.dumps(tables)
