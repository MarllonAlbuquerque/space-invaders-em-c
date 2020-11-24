#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
//TELA 
const int SCREEN_W = 662;
const int SCREEN_H = 400;

//CHÃO
const int FLOOR_H = 60;

//nave
const int NAVE_W = 100;
const int NAVE_H = 50;

//ALIEN
const int ALIEN_W = 50;
const int ALIEN_H = 25;

//FPS
const float FPS = 100;

typedef struct Nave{
	float x;
	ALLEGRO_COLOR cor;
	}Nave;

void initNave(Nave *nave){
	nave -> x = SCREEN_W/2;
	nave ->cor = al_map_rgb(0, 0, 255);
	}
	
void draw_nave(Nave nave){
	float y_base = SCREEN_H - FLOOR_H/2;
	al_draw_filled_triangle(nave.x, y_base - NAVE_H,
	                        nave.x - NAVE_W/2, y_base,
	                        nave.x + NAVE_W/2, y_base,
	                         nave.cor);
	}
	
typedef struct Alien{
		float x, y;
		float x_vel, y_vel;
		ALLEGRO_COLOR cor;
		}Alien;
		
void initAlien(Alien *alien){
	alien -> x=0;
	alien -> y=0;
	alien->x_vel=1;
	alien->y_vel = ALIEN_H;
	alien->cor = al_map_rgb(rand()%256, rand()%256, rand()%256);
	}
		
void draw_alien(Alien alien){
	al_draw_filled_rectangle(alien.x, alien.y,
	                         alien.x + ALIEN_W, alien.y + ALIEN_H,
							 alien.cor );
	}
	
void update_alien(Alien *alien){
	
	if(alien->x + ALIEN_W + alien-> x_vel > SCREEN_W || alien -> x + alien->x_vel < 0){
		alien -> y += alien-> y_vel;
		alien->x_vel *= -1;
		}
	   alien ->x += alien -> x_vel;
	}
	
int alienvence(Alien alien){
	if(alien.y + ALIEN_H > SCREEN_H - FLOOR_H)
	    return 1;
	else 
	  return 0;
	}
	

int main(){
	
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_BITMAP *imagem = NULL;
	
	//inicialização
	if(!al_init()) {
		fprintf(stderr, "failed to initialize allegro!\n");
		return -1;
	}
	
	al_init_image_addon();
	
	//cria uma tela com dimensoes de SCREEN_W, SCREEN_H pixels
	display = al_create_display(SCREEN_W, SCREEN_H);
	if(!display) {
		fprintf(stderr, "failed to create display!\n");
		return -1;
	}
	
	imagem = al_load_bitmap("wall.bmp");
	
	//inicializa o mÃ³dulo de primitivas do Allegro
    if(!al_init_primitives_addon()){
		fprintf(stderr, "failed to initialize primitives!\n");
        return -1;
    }	
	
	//cria um temporizador que incrementa uma unidade a cada 1.0/FPS segundos
    timer = al_create_timer(1.0 / FPS);
    if(!timer) {
		fprintf(stderr, "failed to create timer!\n");
		return -1;
	}
	
	//cria a fila de eventos
	event_queue = al_create_event_queue();
	if(!event_queue) {
		fprintf(stderr, "failed to create event_queue!\n");
		al_destroy_display(display);
		return -1;
	}
	
	//instala o teclado
	if(!al_install_keyboard()) {
		fprintf(stderr, "failed to install keyboard!\n");
		return -1;
	}
	
	//instala o mouse
	if(!al_install_mouse()) {
		fprintf(stderr, "failed to initialize mouse!\n");
		return -1;
	}
	
	//registra na fila os eventos de tela (ex: clicar no X na janela)
	al_register_event_source(event_queue, al_get_display_event_source(display));
	//registra na fila os eventos de teclado (ex: pressionar uma tecla)
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	//registra na fila os eventos de mouse (ex: clicar em um botao do mouse)
	al_register_event_source(event_queue, al_get_mouse_event_source()); 
	//registra na fila os eventos de tempo: quando o tempo altera de t para t+1
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	
	Nave nave;
	initNave(&nave);
	
	Alien alien;
	initAlien(&alien);
	
	
	int playing = 1;
	
	//inicia o temporizador
	al_start_timer(timer);
	
	while(playing){
			
			ALLEGRO_EVENT ev;	
			//espera por um evento e o armazena na variavel de evento ev
			al_wait_for_event(event_queue, &ev);
			
			//se o tipo de evento for um evento do temporizador, ou seja, se o tempo passou de t para t+1
		    if(ev.type == ALLEGRO_EVENT_TIMER) {
				
				
				//DRAWS-------------
				
				al_draw_bitmap(imagem, 0, 0, 0);
				
				draw_nave(nave);
			
			    update_alien(&alien);
			    
				draw_alien(alien);
				
				
				playing =!alienvence(alien);
                
                //-----------------------
                
                
				//atualiza a tela
				al_flip_display();
				
				if(al_get_timer_count(timer)%(int)FPS == 0)
					printf("\n%d segundos se passaram...", (int)(al_get_timer_count(timer)/FPS));
		    }
			
			//se o tipo de evento for o fechamento da tela (clique no x da janela)
			if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
					playing = 0;
				}	
			
			//se o tipo de evento for um pressionar de uma tecla
			else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
					//imprime qual tecla foi
					printf("\ncodigo tecla: %d", ev.keyboard.keycode);
					
				//CONTROLES ---------------------
                  switch(ev.keyboard.keycode){
						
					case ALLEGRO_KEY_LEFT:
						if(nave.x >= 90){nave.x-=10;}
					break;
					
					case ALLEGRO_KEY_RIGHT:
						if(nave.x <= SCREEN_W - 100){nave.x+=10;}
						 
					break;  
					
				//--------------------------------	
						
						}		
				}	
		}
		
		
		
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
	
	return 0;
	}
