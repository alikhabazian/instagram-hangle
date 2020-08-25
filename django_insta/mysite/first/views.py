from django.shortcuts import render
from django.http import HttpResponse
# Create your views here.
import requests
import json



def index(request):


    session =requests.Session()



    jar =requests.cookies.RequestsCookieJar()
    jar.set('sessionid','39188415601%3Avf9L6sXx7w6DA2%3A18')

    session.cookies =jar



    r=session.get('https://www.instagram.com/p/CEMnQPWFmRg/?__a=1')
    x=json.loads(r.text)
    print(x['graphql']['shortcode_media']['edge_media_preview_like']['count'])

    return HttpResponse("this: "+str(x['graphql']['shortcode_media']['edge_media_preview_like']['count']))
