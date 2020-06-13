import urllib.request

request = Request('http://placekitten.com/')

try:
	response = urlopen(request)
	kittens = response.read()
	print (kittens[559:1000])
