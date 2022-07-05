from flask_restful import Resource,reqparse,Api
import pandas as pd
from flask import Flask,request
app = Flask(__name__)
api = Api(app)

def sendData(data):
	# if data=="state":
	d = pd.read_csv("data.csv")
	return str(d.STATE[0])


  
    

class data_to_esp(Resource):
    def get(self,data):
        return sendData(data)
api.add_resource(data_to_esp,'/<string:data>')
if __name__ == '__main__':
    app.run(host='0.0.0.0',debug=True)