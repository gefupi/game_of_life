import pygame
import sys
from pygame.locals import *

pygame.init()

width=800
height=600


screen = pygame.display.set_mode((width,height))

def makePic(str):
	tmp = pygame.Surface((width,height))
	lines = str.split('#')
	x = 0
	y = 0
	while y < len(lines):
		x = 0
		while x < len(lines[y]):
			if lines[y][x]=='1':
				pygame.draw.circle(tmp,(250,250,250),(x*10+5,y*10+5),4)
			x = x +1
		y = y +1
	return tmp

while True:
	for event in pygame.event.get():
		if event.type == KEYDOWN:
			sys.exit()
	inp = raw_input()
	#inp = "000110#000001#011000#110000#010101#000100"
	screen.blit(makePic(inp),(0,0))
	pygame.display.flip()