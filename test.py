import time
import requests


print("Motion detected!")

# Your IFTTT URL with event name, key and json parameters (values)
# r = requests.post('https://maker.ifttt.com/trigger/button_pressed/with/key/f42Co9SZokK9gEjdu_YVOW0rWekQsLiJHrfoD-GkLyx', params={"value1":"none","value2":"none","value3":"none"})
r = requests.post('https://maker.ifttt.com/trigger/button_pressed/with/key/f42Co9SZokK9gEjdu_YVOW0rWekQsLiJHrfoD-GkLyx')
