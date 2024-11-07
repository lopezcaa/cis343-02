import os
import pygame as pg

# Complete me! - TODO
class Enemy(pg.sprite.Sprite):
    def __init__(self, position):
        super(Enemy, self).__init__()
        self.image = pg.image.load(os.path.join('assets', 'Ship1.png')).convert_alpha()
        self.rect = self.image.get_rect()
        self.rect.topleft = position
        self.speed = 1

    def update(self, delta):
        self.rect.x -= self.speed
        
        holding = int(self.rect.x % 150)

        if (0 <= holding < 75) % 2 == 0:
            if holding % 3 == 0:
                self.rect.y += 1
        elif (75 <= holding <= 150) % 2 == 0:
            if holding % 3 == 0:
                self.rect.y -= 1

        if self.rect.x <= 0:
            self.rect.x = 1024  # Reset position after passing off-screen
