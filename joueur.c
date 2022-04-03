void moveLeft(player p)		//la fonction va vérifier si on peut se déplacer vers la gauche et le faire le cas échéant
{
	int x = 0, y = 0;

	x = p->pos.x-1;
	y = p->pos.y;
	

	if (*(*(map + y) + x)!='#')
	{
		p->pos.x = x;
	}

}

void moveRight(player p)		//la fonction va vérifier si on peut se déplacer vers la droite et le faire le cas échéant
{
	int x = 0, y = 0;


	x = p->pos.x+1;
	y = p->pos.y;


	if (*(*(map + y) + (x+1))!='#')
	{
		p->pos.x = x;
	}

}



void moveUp(player p)
{
 int  x = 0, y = 0;
      
	x = p->pos.x;
	y = p->pos.y-1;

	if (*(*(map + y) + x)!='#')//attention a changer
	{
		if(y>=20||(*(*(map + 0)+20)=='#')){
			p->pos.y = y;
			printf("\npos y: %d\n",y+1);
		}
		else{
			printf("\npos y: %d\n",y+1);
			loadMap(41, 40, p);
		}
	}     
	
}

void moveDown(player p)
{
 int  x = 0, y = 0;
 
   x = p->pos.x;
   y = p->pos.y+1;
   if (*(*(map + (y+1)) + x) !='#')
      {
		if(y<38){
			p->pos.y = y;
			printf("\npos y: %d\n",y+1);
		}
		else{
			printf("\npos y: %d\n",y+1);
			loadMap(41, 40, p);
		}
      }
}
//void movePlayer(
