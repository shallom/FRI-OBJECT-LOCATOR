#!/usr/bin/ruby

require 'rubygems'
require 'simple_oauth'
require 'cloudsight'

class CloudSightInterface

def setAuth()
	Cloudsight.oauth_options = {
  	consumer_key: 'DhJLTpx-xP1qYKq75WIhvQ',
  	consumer_secret: '_6Qt_7yPQPgd_iZvfOWneA'
	}
end

def sendPictureAndGetResponse(picture_name)
x=320
y=240
	requestData = Cloudsight::Request.send(locale: 'en', :file => File.open(picture_name), :focus=>{:x => x, :y => y})

	Cloudsight::Response.retrieve(requestData['token']) do |responseData|
	puts responseData
	end
end

end

cloudSight=CloudSightInterface.new
cloudSight.setAuth()
cloudSight.sendPictureAndGetResponse('wolf.png')
