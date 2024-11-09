import os
import pygame as pg

# Create a Player class that is a subclass of pygame.sprite.Sprite
# Load an image as such:
#        self.image = pg.image.load(os.path.join('assets', 'Ship6.png')).convert_alpha()
# The position is controlled by the rectangle surrounding the image.
# Set self.rect = self.image.get_rect().  Then make changes to the 
# rectangle x, y or centerx and centery to move the object.

class Player(pg.sprite.Sprite):
    def __init__(self):
        super(Player, self).__init__()
        self.image = pg.image.load(os.path.join('assets', 'Ship6.png')).convert_alpha()
        self.rect = self.image.get_rect()
        self.rect.centerx = 100
        self.rect.centery = 450 
        self.speed = 500

    def draw(self, screen):
        screen.blit(self.image, self.rect)

    def update(self, delta):
        pass

    def up(self, delta):
        if self.rect.top > 0:
            self.rect.centery -= self.speed * delta

    def down(self, delta):
        if self.rect.bottom < 768:
            self.rect.centery += self.speed * delta
    
    def left(self, delta):
        if self.rect.x >= 30:
            self.rect.centerx -= self.speed * delta

    def right(self, delta):
        if self.rect.x < 400:
            self.rect.centerx += self.speed * delta
