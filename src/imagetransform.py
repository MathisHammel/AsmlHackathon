from PIL import Image
im = Image.open('C:/Users/Hackaton/ASML/AsmlHackathon/asml_logo.bmp')
assert im.size == (32,32)

l=[]
for x in range(8):
    ll=[]
    for y in range(32):
        ll.append(255 if sum(im.getpixel((x,y))) > 200 else 0)
    l.append(ll)
print str(l).replace('[','{').replace(']','}')