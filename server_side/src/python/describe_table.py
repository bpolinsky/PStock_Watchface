#!/usr/bin/env python

import boto3

# Remember to set AWS_ACCESS_KEY_ID and AWS_SECRET_ACCESS_KEY in
# the environment before running this program.

AWS_REGION = 'us-east-1'

db = boto3.client('dynamodb',
                  region_name = AWS_REGION)
                    
table = db.describe_table(TableName = '2014')
print table['Table']['KeySchema']
