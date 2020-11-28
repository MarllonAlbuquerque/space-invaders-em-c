#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

//------------------------------





int main(){
	
	//TELA 
    int SCREEN_W = 662;
    int SCREEN_H = 400;

    //CHÃO
    int FLOOR_H = 60;

	//FPS
	float FPS = 100;
	
	//NAVE-----------------
	int navex = 331;
	int navey = 300;
	
	
	//ALIENS-----------------
	int velocidadealien = 1;
	
	
	int alienx = 0;
	int alienx2 = 50;
	int alienx3 = 180;
	int alienx4 = 280;
	int alienx5 = 320;
	int alienx6 = 400;
	int alienx7 = 328;
	int alienx8 = 240;
	int alienx9 = 580;
	int alienx10 = 80;
	int alieny = -10;
	int alieny2 = -300;
	int alieny3 = -500;
	int alieny4 = -600;
	int alieny5 = -790;
	int alieny6 = -850;
	int alieny7 = -1000;
	int alieny8 = -820;
	int alieny9 = -1100;
	int alieny10 = -1400;
	
	
	
	
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_BITMAP *imagem = NULL;
	ALLEGRO_BITMAP *personagem = NULL;
	ALLEGRO_BITMAP *alien = NULL; ALLEGRO_BITMAP *alien2 = NULL; ALLEGRO_BITMAP *alien3 = NULL; ALLEGRO_BITMAP *alien4 = NULL; ALLEGRO_BITMAP *alien5 = NULL;
	ALLEGRO_BITMAP *alien6 = NULL; ALLEGRO_BITMAP *alien7 = NULL; ALLEGRO_BITMAP *alien8 = NULL; ALLEGRO_BITMAP *alien9 = NULL; ALLEGRO_BITMAP *alien10 = NULL;
	ALLEGRO_BITMAP *alienmorto = NULL;
	
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
	
	
	
	
	//CARREGAR IMAGENS
	imagem = al_load_bitmap("wall.bmp");
	personagem = al_load_bitmap("navee.bmp");
	alien = al_load_bitmap("alien1.bmp");
	alien2 = al_load_bitmap("alien2.bmp");
	alien3 = al_load_bitmap("alien1.bmp");
	alien4 = al_load_bitmap("alien1.bmp");
	alien5 = al_load_bitmap("alien1.bmp");
	alien6 = al_load_bitmap("alien1.bmp");
	alien7 = al_load_bitmap("alien2.bmp");
	alien8 = al_load_bitmap("alien2.bmp");
	alien9 = al_load_bitmap("alien2.bmp");
	alien10 = al_load_bitmap("alien2.bmp");
	alienmorto = al_load_bitmap("navemorta.bmp");
	
	
	//RETIRAR FUNDO
	al_convert_mask_to_alpha(personagem,al_map_rgb(255,0,255));
	al_convert_mask_to_alpha(alien,al_map_rgb(255,0,255));
	al_convert_mask_to_alpha(alien2,al_map_rgb(255,0,255));
	al_convert_mask_to_alpha(alien3,al_map_rgb(255,0,255));
	al_convert_mask_to_alpha(alien4,al_map_rgb(255,0,255));
	al_convert_mask_to_alpha(alien5,al_map_rgb(255,0,255));
	al_convert_mask_to_alpha(alien6,al_map_rgb(255,0,255));
	al_convert_mask_to_alpha(alien7,al_map_rgb(255,0,255));
	al_convert_mask_to_alpha(alien8,al_map_rgb(255,0,255));
	al_convert_mask_to_alpha(alien9,al_map_rgb(255,0,255));
	al_convert_mask_to_alpha(alien10,al_map_rgb(255,0,255));
	al_convert_mask_to_alpha(alienmorto,al_map_rgb(255,0,255));
	
	
	
	
	//inicializa o modulo de primitivas do Allegro
    if(!al_init_primitives_addon()){
		fprintf(stderr, "failed to initialize primitives!\n");
        return -1;
    }	
	
	//cria um temporizador
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
	
	int playing = 1;
	
	//inicia o temporizador
	al_start_timer(timer);
	
	
	
	
	while(playing){
			
			ALLEGRO_EVENT ev;	
			//espera por um evento e o armazena na variavel de evento ev
			al_wait_for_event(event_queue, &ev);
			
			//se o tipo de evento for um evento do temporizador, ou seja, se o tempo passou de t para t+1
		    if(ev.type == ALLEGRO_EVENT_TIMER) {
				
				//Queda dos aliens
					if(alieny10 < SCREEN_H){
						alieny  += velocidadealien;
						alieny2 += velocidadealien;
						alieny3 += velocidadealien;
						alieny4 += velocidadealien;
						alieny5 += velocidadealien;
						alieny6 += velocidadealien;
						alieny7 += velocidadealien;
						alieny8 += velocidadealien;
						alieny9 += velocidadealien;
						alieny10 += velocidadealien;
						}
						
			        
						
						
				//DRAWS-------------
				
				al_draw_bitmap(imagem, 0, 0, 0);
				
				al_draw_bitmap(personagem, navex, navey, 0);
				
				//Ordem de queda
				
				al_draw_bitmap(alien, alienx, alieny, 0);
				al_draw_bitmap(alien2, alienx2, alieny2, 0);
				al_draw_bitmap(alien3, alienx3, alieny3, 0);
				al_draw_bitmap(alien4, alienx4, alieny4, 0);
				al_draw_bitmap(alien5, alienx5, alieny5, 0);
				al_draw_bitmap(alien6, alienx6, alieny6, 0);
				al_draw_bitmap(alien7, alienx7, alieny7, 0);
				al_draw_bitmap(alien8, alienx8, alieny8, 0);
				al_draw_bitmap(alien9, alienx9, alieny9, 0);
				al_draw_bitmap(alien10, alienx10, alieny10, 0);
			    
				
				
				
				
				
				
				
				
				//DETECTOR DE COLISÃO --------
					if (alienx + 87 > navex && alienx < navex + 86 && alieny + 86 > navey && alieny < navey + 86 ){ 
			            al_draw_bitmap(alienmorto, alienx, alieny, 0);
			            alienx = 660;
			            alieny = -299;
			          }
			          if (alienx2 + 87 > navex && alienx2 < navex + 86 && alieny2 + 86 > navey && alieny2 < navey + 86 ){ 
			            al_draw_bitmap(alienmorto, alienx2, alieny2, 0);
			            alienx2 = 660;
			            alieny2 = -299;
			          }
			          if (alienx3 + 87 > navex && alienx3 < navex + 86 && alieny3 + 86 > navey && alieny3 < navey + 86 ){ 
			            al_draw_bitmap(alienmorto, alienx3, alieny3, 0);
			            alienx3 = 660;
			            alieny3 = -299;
			          }
			          if (alienx4 + 87 > navex && alienx4 < navex + 86 && alieny4 + 86 > navey && alieny4 < navey + 86 ){ 
			            al_draw_bitmap(alienmorto, alienx4, alieny4, 0);
			            alienx4 = 660;
			            alieny4 = -299;
			          }
			          if (alienx5 + 87 > navex && alienx5 < navex + 86 && alieny5 + 86 > navey && alieny5 < navey + 86 ){ 
			            al_draw_bitmap(alienmorto, alienx5, alieny5, 0);
			            alienx5 = 660;
			            alieny5 = -299;
			          }
			          if (alienx6 + 87 > navex && alienx6 < navex + 86 && alieny6 + 86 > navey && alieny6 < navey + 86 ){ 
			            al_draw_bitmap(alienmorto, alienx6, alieny6, 0);
			            alienx6 = 660;
			            alieny6 = -299;
			          }
			          if (alienx7 + 87 > navex && alienx7 < navex + 86 && alieny7 + 86 > navey && alieny7 < navey + 86 ){ 
			            al_draw_bitmap(alienmorto, alienx7, alieny7, 0);
			            alienx7 = 660;
			            alieny7 = -299;
			          }
			          if (alienx8 + 87 > navex && alienx8 < navex + 86 && alieny8 + 86 > navey && alieny8 < navey + 86 ){ 
			            al_draw_bitmap(alienmorto, alienx8, alieny8, 0);
			            alienx8 = 660;
			            alieny8 = -299;
			          }
			          if (alienx9 + 87 > navex && alienx9 < navex + 86 && alieny9 + 86 > navey && alieny9 < navey + 86 ){ 
			            al_draw_bitmap(alienmorto, alienx9, alieny9, 0);
			            alienx9 = 660;
			            alieny9 = -299;
			          }
			          if (alienx10 + 87 > navex && alienx10 < navex + 86 && alieny10 + 86 > navey && alieny10 < navey + 86 ){ 
			            al_draw_bitmap(alienmorto, alienx10, alieny10, 0);
			            alienx10 = 660;
			            alieny10 = -299;
			          }
			          
			          
			    //-------------------------
										          
				if(alieny, alieny2, alieny3, alieny4, alieny5, alieny6, alieny7, alieny8, alieny9, alieny10 >= 350){playing = 0;}
			        
				
                
				
                //-------------------------
                
                
				//atualiza a tela
				al_flip_display();
				
				if(al_get_timer_count(timer)%(int)FPS == 0)
					printf("\n%d segundos se passaram...", (int)(al_get_timer_count(timer)/FPS));
					
					
					
					
					
		    }
			
			//se o tipo de evento for o fechamento 
			if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
					playing = 0;
				}	
			
			//se o tipo de evento for um pressionar de uma tecla
			else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
					//imprime qual tecla foi
					printf("\ncodigo tecla: %d", ev.keyboard.keycode);
					
										
				//CONTROLES ---------------------
                  switch(ev.keyboard.keycode){
						
					case ALLEGRO_KEY_RIGHT:
						if(navex <= 550){navex += 50;}
					break;
					
					case ALLEGRO_KEY_LEFT:
						if(navex >= 30){navex -= 50;}
					break;
				
					 
				//--------------------------------	
				
				
				
				
				
						
						}		
				}
				
				
				
					
		}
		
		
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
	
	return 0;
	}
