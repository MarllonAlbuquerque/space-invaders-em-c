#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_native_dialog.h>

//------------------------------


int main(){
	
	//TELA 
    int SCREEN_W = 662;//LARGURA
    int SCREEN_H = 400;//ALTURA

	//FPS
	float FPS = 100;
	
	//NAVE-----------------
	int navex = 331;
	int navey = 300;
	
	// TIRO NAVE---------------------
	int tirovel= 5;
	int tiroy = navey;
	int tirox = navex + 40;
	int starttiro = 0;
	
	//CONTADOR DE ALIENS MORTOS
	int aux = 0;
	
	//ALIENS-----------------
	float velocidadealien = 2;
	
	
	//X DOS ALIENS 
	int alienx = 10;
	int alienx2 = 184;
	int alienx3 = 358;
	int alienx4 = 530;
	int alienx7 = 97;
	int alienx9 = 269;
	int alienx10 = 450;
	int alienx11 = 10;
	int alienx12 = 184;
	int alienx13 = 358;
	int alienx14 = 530;
	
	
	//Y DOS ALIENS
	int alieny = 10;
	int alieny2 = 10;
	int alieny3 = 10;
	int alieny4 = 10;
	int alieny7 = 60;
	int alieny9 = 60;
	int alieny10 = 60;
	int alieny11 = 110;
	int alieny12 = 110;
	int alieny13 = 110;
	int alieny14 = 110;

	
	
	//TIRO ALIENS----------------------
	int tirovelalien = 1;
	int tiroalienx = alienx + 35;
	int tiroalieny = alieny + 10;
	int tiroalienx2 = alienx7 + 35;
	int tiroalieny2 = alieny7 + 10;
	int tiroalienx3 = alienx14 + 35;
	int tiroalieny3 = alieny14 + 10;


	
	//PONTEIROS PARA CADA OBJETO
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_BITMAP *imagem = NULL;
	ALLEGRO_BITMAP *personagem = NULL;
	ALLEGRO_BITMAP *alien = NULL; ALLEGRO_BITMAP *alien2 = NULL; ALLEGRO_BITMAP *alien3 = NULL; ALLEGRO_BITMAP *alien4 = NULL;
	ALLEGRO_BITMAP *alien7 = NULL; ALLEGRO_BITMAP *alien9 = NULL; ALLEGRO_BITMAP *alien10 = NULL;
	ALLEGRO_BITMAP *alien11 = NULL; ALLEGRO_BITMAP *alien12 = NULL; ALLEGRO_BITMAP *alien13 = NULL; ALLEGRO_BITMAP *alien14 = NULL; 
	ALLEGRO_BITMAP *alienmorto = NULL;
	ALLEGRO_BITMAP *tiro = NULL;
	ALLEGRO_BITMAP *tiroalien = NULL;
	ALLEGRO_BITMAP *tiroalien2 = NULL;
	ALLEGRO_BITMAP *tiroalien3 = NULL;
	ALLEGRO_BITMAP *personagemmorto = NULL;
	ALLEGRO_BITMAP *gameover = NULL;
	
	
	//inicialização
	if(!al_init()) {
		fprintf(stderr, "failed to initialize allegro!\n");
		return -1;
	}
	
	// O nosso arquivo de fonte
    ALLEGRO_FONT *fonte = NULL;
    
    // Inicialização do add-on para uso de fontes
    al_init_font_addon();
	
	al_init_image_addon();
	
	// Inicialização do add-on para uso de fontes True Type
    if (!al_init_ttf_addon()){
        return -1;
    }
	
	//cria uma tela com dimensoes de SCREEN_W, SCREEN_H pixels
	display = al_create_display(SCREEN_W, SCREEN_H);
	if(!display) {
		fprintf(stderr, "failed to create display!\n");
		return -1;
	}
	
	// Carregando o arquivo de fonte
    fonte = al_load_font("arial.ttf", 48, 0);
    if (!fonte){
        al_destroy_display(display);
        return -1;
    }
	
	
	
	
	//CARREGAR IMAGENS
	imagem = al_load_bitmap("wall.bmp");
	personagem = al_load_bitmap("naveoriginal.bmp");
	personagemmorto = al_load_bitmap("originalmorto.bmp");
	alien = al_load_bitmap("alien1.bmp");
	alien2 = al_load_bitmap("alien2.bmp");
	alien3 = al_load_bitmap("alien1.bmp");
	alien4 = al_load_bitmap("alien1.bmp");
	alien7 = al_load_bitmap("alien2.bmp");
	alien9 = al_load_bitmap("alien2.bmp");
	alien10 = al_load_bitmap("alien2.bmp");
	alien11 = al_load_bitmap("alien1.bmp");
	alien12 = al_load_bitmap("alien2.bmp");
	alien13 = al_load_bitmap("alien2.bmp");
	alien14 = al_load_bitmap("alien2.bmp");
	alienmorto = al_load_bitmap("navemorta.bmp");
	tiro = al_load_bitmap("tiro.bmp");
	tiroalien = al_load_bitmap("tiro.bmp");
	tiroalien2 = al_load_bitmap("tiro.bmp");
	tiroalien3 = al_load_bitmap("tiro.bmp");
	gameover = al_load_bitmap("GAMEOVER.bmp");
	
	
	//RETIRAR FUNDO
	al_convert_mask_to_alpha(personagem,al_map_rgb(255,0,255));
	al_convert_mask_to_alpha(personagemmorto,al_map_rgb(255,0,255));
	al_convert_mask_to_alpha(alien,al_map_rgb(255,0,255));
	al_convert_mask_to_alpha(alien2,al_map_rgb(255,0,255));
	al_convert_mask_to_alpha(alien3,al_map_rgb(255,0,255));
	al_convert_mask_to_alpha(alien4,al_map_rgb(255,0,255));
	al_convert_mask_to_alpha(alien7,al_map_rgb(255,0,255));
	al_convert_mask_to_alpha(alien9,al_map_rgb(255,0,255));
	al_convert_mask_to_alpha(alien10,al_map_rgb(255,0,255));
	al_convert_mask_to_alpha(alien11,al_map_rgb(255,0,255));
	al_convert_mask_to_alpha(alien12,al_map_rgb(255,0,255));
	al_convert_mask_to_alpha(alien13,al_map_rgb(255,0,255));
	al_convert_mask_to_alpha(alien14,al_map_rgb(255,0,255));
	al_convert_mask_to_alpha(alienmorto,al_map_rgb(255,0,255));
	al_convert_mask_to_alpha(tiro,al_map_rgb(255,0,255));
	al_convert_mask_to_alpha(tiroalien,al_map_rgb(255,0,255));
	al_convert_mask_to_alpha(tiroalien2,al_map_rgb(255,0,255));
	al_convert_mask_to_alpha(tiroalien3,al_map_rgb(255,0,255));
	
	
	
	
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
	
	
	
	//inicia o temporizador
	al_start_timer(timer);
	
	int playing = 1;
	
	
	
	while(playing){

			ALLEGRO_EVENT ev;	
			//espera por um evento e o armazena na variavel de evento ev
			al_wait_for_event(event_queue, &ev);
		
			//se o tipo de evento for um evento do temporizador, ou seja, se o tempo passou de t para t+1
		    if(ev.type == ALLEGRO_EVENT_TIMER) {
				
						
				
				
					
				//SISTEMA DE TIRO-----------------------	
				//TIRO NAVE :	
				if(starttiro){if(tiroy >=-10){tiroy -= tirovel;} if(tiroy ==-10){tiroy = navey; starttiro = 0;}}
				
				//TIRO ALIEN :
				if(tiroalieny <= 400){tiroalieny += tirovelalien; if(tiroalieny == 400){tiroalieny = alieny + 10; tiroalienx = alienx + 35;}} 
				if(tiroalieny2 <= 400){tiroalieny2 += tirovelalien; if(tiroalieny2 == 400){tiroalieny2 = alieny7 + 10;  tiroalienx2 = alienx7 + 35;}} 
				if(tiroalieny3 <= 400){tiroalieny3 += tirovelalien; if(tiroalieny3 == 400){tiroalieny3 = alieny14 + 10; tiroalienx3 = alienx14 + 35;}}
				 
				  
						
					
				//DRAWS-------------
				
				//FUNDO
				al_draw_bitmap(imagem, 0, 0, 0);
				
				
				//NAVE 
				al_draw_bitmap(personagem, navex, navey, 0);
				
				//ALIENS
				al_draw_bitmap(alien, alienx, alieny, 0);
				al_draw_bitmap(alien2, alienx2, alieny2, 0);
				al_draw_bitmap(alien3, alienx3, alieny3, 0);
				al_draw_bitmap(alien4, alienx4, alieny4, 0);
				al_draw_bitmap(alien7, alienx7, alieny7, 0);
				al_draw_bitmap(alien9, alienx9, alieny9, 0);
				al_draw_bitmap(alien10, alienx10, alieny10, 0);
				al_draw_bitmap(alien11, alienx11, alieny11, 0);
				al_draw_bitmap(alien12, alienx12, alieny12, 0);
				al_draw_bitmap(alien13, alienx13, alieny13, 0);
				al_draw_bitmap(alien14, alienx14, alieny14, 0);
				
				//TIROS
				al_draw_bitmap(tiro, tirox, tiroy, 0);
				al_draw_bitmap(tiroalien, tiroalienx, tiroalieny, 0);
				al_draw_bitmap(tiroalien2, tiroalienx2, tiroalieny2, 0);
				al_draw_bitmap(tiroalien3, tiroalienx3, tiroalieny3, 0);
					
				
			    
				
				//LINHA DE ALINS 1 --------------
				if(alienx <= SCREEN_W){
					alienx += velocidadealien; tiroalienx += velocidadealien;
					alienx2 += velocidadealien;
					alienx3 += velocidadealien;
					alienx4 += velocidadealien;
				if(alienx > SCREEN_W){
					alienx = -530;
					alienx2 = -358;
					alienx3 = -184;
					alienx4 = -10;
					}}
					
					
				//LINHA DE ALINS 2 -------------	
				if(alienx10 >= -662){
					alienx7 -= velocidadealien; tiroalienx2 -= velocidadealien;
					alienx9 -= velocidadealien;
					alienx10 -= velocidadealien;
				if(alienx10 == -662){
					alienx7 = 931;
					alienx9 = 716;
					alienx10 = 1112;
					}
				 }
				 
				 
				 //LINHA DE ALINS 3 --------------
				if(alienx11 <= SCREEN_W){
					alienx11 += velocidadealien;
					alienx12 += velocidadealien;
					alienx13 += velocidadealien;
					alienx14 += velocidadealien; tiroalienx3 += velocidadealien;
				if(alienx11 > SCREEN_W){
					alienx11 = -530;
					alienx12 = -358;
					alienx13 = -184;
					alienx14 = -10;
					}}
				
				
				
				
				
				
				//DETECTOR DE COLISÃO DA NAVE --------
					if (navex + 86 > tiroalienx && navex < tiroalienx + 9 && navey + 9 > tiroalieny && navey < tiroalieny + 9 ){
						al_draw_bitmap(personagemmorto, navex, navey, 0);
						al_rest(1.0);
						playing =0;
						
			          }
			        if (navex + 86 > tiroalienx2 && navex < tiroalienx2 + 9 && navey + 9 > tiroalieny2 && navey < tiroalieny2 + 9 ){
						al_draw_bitmap(personagemmorto, navex, navey, 0);
						al_rest(1.0); 
						playing =0; 
						
			          }
			        if (navex + 86 > tiroalienx3 && navex < tiroalienx3 + 9 && navey + 9 > tiroalieny3 && navey < tiroalieny3 + 9 ){
						al_draw_bitmap(personagemmorto, navex, navey, 0);
						al_rest(1.0); 
						playing =0; 
						
			          }
				
				
				
				
				//DETECTOR DE COLISÃO DOS ALIEN--------
					if (alienx + 87 > tirox && alienx < tirox + 9 && alieny + 9 > tiroy && alieny < tiroy + 9 ){ 
			            al_draw_bitmap(alienmorto, alienx, alieny, 0);
			            alienx = -660;
			            alieny = -299;
			            tiroy = navey;
			            starttiro = 0;
			            tiroalienx = 700;
			            tiroalieny = 700;
			            aux += 1;
			          }
			        if (alienx2 + 87 > tirox && alienx2 < tirox + 9 && alieny2 + 9 > tiroy && alieny2 < tiroy + 9 ){ 
			            al_draw_bitmap(alienmorto, alienx2, alieny2, 0);
			            alienx2 = -660;
			            alieny2 = -299;
			            tiroy = navey;
			            starttiro = 0;
			            aux += 1;
			          }
			        if (alienx3 + 87 > tirox && alienx3 < tirox + 9 && alieny3 + 9 > tiroy && alieny3 < tiroy + 9 ){ 
			            al_draw_bitmap(alienmorto, alienx3, alieny3, 0);
			            alienx3 = -660;
			            alieny3 = -299;
			            tiroy = navey;
			            starttiro = 0;
			            aux += 1;
			          }
			        if (alienx4 + 87 > tirox && alienx4 < tirox + 9 && alieny4 + 9 > tiroy && alieny4 < tiroy + 9 ){ 
			            al_draw_bitmap(alienmorto, alienx4, alieny4, 0);
			            alienx4 = -660;
			            alieny4 = -299;
			            tiroy = navey;
			            starttiro = 0;
			            aux += 1;
			          }
			          if (alienx7 + 87 > tirox && alienx7 < tirox + 9 && alieny7 + 9 > tiroy && alieny7 < tiroy + 9 ){ 
			            al_draw_bitmap(alienmorto, alienx7, alieny7, 0);
			            alienx7 = -660;
			            alieny7 = -299;
			            tiroy = navey;
			            starttiro = 0;
			            tiroalienx2 = 700;
			            tiroalieny2 = 700;
			            aux += 1;
			          }
			        if (alienx9 + 87 > tirox && alienx9 < tirox + 9 && alieny9 + 9 > tiroy && alieny9 < tiroy + 9 ){ 
			            al_draw_bitmap(alienmorto, alienx9, alieny9, 0);
			            alienx9 = -660;
			            alieny9 = -299;
			            tiroy = navey;
			            starttiro = 0;
			            aux += 1;
			          }
			        if (alienx10 + 87 > tirox && alienx10 < tirox + 9 && alieny10 + 9 > tiroy && alieny10 < tiroy + 9 ){ 
			            al_draw_bitmap(alienmorto, alienx10, alieny10, 0);
			            alienx10 = -660;
			            alieny10 = -299;
			            tiroy = navey;
			            starttiro = 0;
			            aux += 1;
			          }
			        if (alienx11 + 87 > tirox && alienx11 < tirox + 9 && alieny11 + 9 > tiroy && alieny11 < tiroy + 9 ){ 
			            al_draw_bitmap(alienmorto, alienx11, alieny11, 0);
			            alienx11 = -660;
			            alieny11 = -299;
			            tiroy = navey;
			            starttiro = 0;
			            aux += 1;
			          }
			        if (alienx12 + 87 > tirox && alienx12 < tirox + 9 && alieny12 + 9 > tiroy && alieny12 < tiroy + 9 ){ 
			            al_draw_bitmap(alienmorto, alienx12, alieny12, 0);
			            alienx12 = -660;
			            alieny12 = -299;
			            tiroy = navey;
			            starttiro = 0;
			            aux += 1;
			          }
			        if (alienx13 + 87 > tirox && alienx13 < tirox + 9 && alieny13 + 9 > tiroy && alieny13 < tiroy + 9 ){ 
			            al_draw_bitmap(alienmorto, alienx13, alieny13, 0);
			            alienx13 = -660;
			            alieny13 = -299;
			            tiroy = navey;
			            starttiro = 0;
			            aux += 1;
			          }
			        if (alienx14 + 87 > tirox && alienx14 < tirox + 9 && alieny14 + 9 > tiroy && alieny14 < tiroy + 9 ){ 
			            al_draw_bitmap(alienmorto, alienx14, alieny14, 0);
			            alienx14 = -660;
			            alieny14 = -299;
			            tiroy = navey;
			            starttiro = 0;
			            tiroalienx3 = 700;
			            tiroalieny3 =  700;
			            aux += 1;
			          }
			          
			    
			    
			    
				
				      
			    //NAVE GANHA --------------------    
			     if(aux == 11 ){
						if(navey >= 200){navey -= 1;}
						if(navey == 200){playing = 0;}
						}
				
			        
				
                
                
                
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
						if(navex <= 550){navex += 50; tirox += 50;}
					break;
					
					case ALLEGRO_KEY_LEFT:
						if(navex >= 30){navex -= 50; tirox -= 50;}
					break;
					
					case 
					    ALLEGRO_KEY_SPACE:
							starttiro += 1;
					break;
					
						}
						
				}
				
				
	    }

				
     al_destroy_display(display);
     al_destroy_timer(timer);
     al_destroy_event_queue(event_queue);
     al_destroy_font(fonte);
     
     
    return 0;	
}

