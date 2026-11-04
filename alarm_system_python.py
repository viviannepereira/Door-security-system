import pygame

import threading

import serial

ser = serial.Serial('COM3', 9600)

current_security = "safe"



def read_serial_data():
    global current_security



    while True:

        data = ser.readline().decode().strip()


        if int(data) == 1:

            current_security = "safe"

        elif int(data) == 0:

            current_security = "intruder!!"

    print(data)




threading.Thread(target=read_serial_data, daemon=True).start()



pygame.init()

screen = pygame.display.set_mode((500, 500))

clock = pygame.time.Clock()

running = True

pygame.display.set_caption("Alarm system")

game_font = pygame.font.SysFont("Arial", 45)



while running:


    for event in pygame.event.get():

        if event.type == pygame.QUIT:

            running = False



    if current_security == "safe":

        text_surface = game_font.render(current_security, True, (255, 255, 255))

    if current_security == "intruder!!":

        text_surface = game_font.render(current_security, True, (255, 0, 0))



    # display on screen

    screen.fill("black")

    screen.blit(text_surface, (100, 200))



    pygame.display.flip()



    clock.tick(60)



pygame.quit()