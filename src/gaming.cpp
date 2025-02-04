#include "../include/gaming.hpp"

void Gaming::gameLogic(){
    int score_player1=0, score_player2=0;
    int game_mod=-1;
    
    //Construindo a dimensão do círculo e sua posição.
    ball.setCircleRadius(20);
    ball.setCirclePosition(640, 400);
    Vector2 ball_position;

    //Construindo as dimensões das "raquetes" e suas respectivas posições.
    racketPlayer.setRacketDimensions(20,120);
    racketPlayer.setRacketPosition(1250,340);

    racketPlayer2.setRacketDimensions(20, 120);
    racketPlayer2.setRacketPosition(10, 340);

    racketComputer.setRacketDimensions(20, 120);
    racketComputer.setRacketPosition(10, 340);

    InitWindow(screen_width, screen_heigh, "Ping-Pong Game");
    SetTargetFPS(60);

    //Construindo as imagem dos butões. 
    Button player1{"graphics/1_jogador.png", {450, 520}};
    Button player2{"graphics/2_jogadores.png", {660, 520}};
    Button exit{"graphics/exit_button.png", {660, 610}};
    Button exitWinnerScreen{"graphics/exit_button.png", {580, 450}};
    Button torneio {"graphics/torneio_button.png", {450,610}};

    Texture2D texture_init_screen = geraTextura("graphics/init_screen.png");
    
    while (WindowShouldClose()==false && game_mod!=0)
    {
        ball_position = ball.getCirclePosition();

        if(game_mod==-1){
            game_mod=this->initialScreen(player1, player2, exit, torneio, texture_init_screen);
            if (game_mod!=0)
            {
                
                for(int i = 3; i>0; i--){
                    DrawText(TextFormat("A partida começa em: %d", i), 200, 300, 80, WHITE);
                    this->drawingObjects(screen_width, screen_heigh, score_player1, score_player2, game_mod);
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                    if (game_mod==2){
                        DrawText(TextFormat("Jogador 1"), 800, 450, 80, WHITE);
                        DrawText(TextFormat("Jogador 2"), 100, 450, 80, WHITE);
                    }else{
                        DrawText(TextFormat("Jogador 1"), 800, 450, 80, WHITE);
                        DrawText(TextFormat("Computador"), 100, 450, 80, WHITE);
                    }
                }          
            }
        }

        // Updating positions:
        racketPlayer.updateRacketPositions();
        //Ambos os ifs checam qual foi modo selecionado para que seja atualizada apenas a posição da raquete correspondente a ele. 
        if(game_mod==1){racketComputer.updateRacketCompPositions(ball_position);}
        if(game_mod==2){racketPlayer2.updateRacketPositions_pl2();}
        int check_score = ball.updatePosition();
       
        // Check collisions:
        if(CheckCollisionCircleRec(ball.getCirclePosition(), ball.getCircleRadius(), 
        Rectangle{racketPlayer.getRacketPosition().x, racketPlayer.getRacketPosition().y, racketPlayer.getRacketDimensions().x, racketPlayer.getRacketDimensions().y})){
            ball.setSpeedCollisionX();
        }

        if (game_mod==1) //Checa se o modo de jogo selecionado foi o de 1 jogador para que seja verifica a colisão com a raquete controlada pelo computador
        {
            if(CheckCollisionCircleRec(ball.getCirclePosition(), ball.getCircleRadius(), 
            Rectangle{racketComputer.getRacketPosition().x, racketComputer.getRacketPosition().y, racketComputer.getRacketDimensions().x, racketComputer.getRacketDimensions().y})){
                ball.setSpeedCollisionX();
            }  

        }

        if (game_mod==2) //Checa se o modo de jogo selecionado foi o de 2 jogadores para que seja verifica a colisão com a raquete controlada pelo outro jogador
        {
            if(CheckCollisionCircleRec(ball.getCirclePosition(), ball.getCircleRadius(), 
            Rectangle{racketPlayer2.getRacketPosition().x, racketPlayer2.getRacketPosition().y, racketPlayer2.getRacketDimensions().x, racketPlayer2.getRacketDimensions().y})){
                ball.setSpeedCollisionX();
            }        
        }

        //Check for scored:this->initialScreen(player1, player2, exit, torneio, texture_init_screen);
        this->checkScore(check_score, &score_player1, &score_player2);

        // string vencedor = (score_player1==5) ? "Parabéns Jogador 1!" : "Parabéns Jogador 2!";

        // Drawing objects:
        this->drawingObjects(screen_width, screen_heigh, score_player1, score_player2, game_mod);

        if(this->pontoMarcado){
            this->pontoMarcado = false;
            reinitGame();
        }

        if(game_mod==2 && (score_player1==5 || score_player2==5)){
            Texture2D winnertext = geraTextura("graphics/winnerTournamentScreen.png");
            string vencedorMessag = (score_player1==5) ? "Parabéns Jogador 1" : "Parabéns Jogador 2";

            while (true)
            {
                bool mouseIsPressed = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
                Vector2 mousePosition = GetMousePosition();

                if(exitWinnerScreen.isPressed(mousePosition, mouseIsPressed)){
                    break;
                }

                BeginDrawing();
                    ClearBackground(this->green);
                    DrawTexture(winnertext, 0, 0, WHITE);
                    escreveNaTela(vencedorMessag, 640, 220, 80);
                    escreveNaTela("Você foi o vencedor!", 640, 300, 80);
                    exitWinnerScreen.Draw(170, 90);
                EndDrawing();
            }
            score_player1 = 0;
            score_player2 = 0;
            game_mod = -1;
        }

        if(game_mod==1 && score_player1==5){
            Texture2D winnerText = geraTextura("graphics/winnerTournamentScreen.png");
            string vencedorMessag = "Parabéns Jogador";

            while (true)
            {
                bool mouseIsPressed = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
                Vector2 mousePosition = GetMousePosition();

                if(exitWinnerScreen.isPressed(mousePosition, mouseIsPressed)){
                    break;
                }

                BeginDrawing();
                    ClearBackground(this->green);
                    DrawTexture(winnerText, 0, 0, WHITE);
                    escreveNaTela(vencedorMessag, 640, 220, 80);
                    escreveNaTela("Você foi o vencedor!", 640, 300, 80);
                    exitWinnerScreen.Draw(170, 90);
                EndDrawing();
            }
            score_player1 = 0;
            score_player2 = 0;
            game_mod = -1;
        } 
        
        if(game_mod==1 && score_player2==5){
            std::cout << "Entrou na condição" << std::endl;
            Texture2D lostText = geraTextura("graphics/lost_screen.png");

            while (true)
            {
                bool mouseIsPressed = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
                Vector2 mousePosition = GetMousePosition();

                if(exitWinnerScreen.isPressed(mousePosition, mouseIsPressed)){
                    break;
                }

                BeginDrawing();
                    ClearBackground(this->green);
                    DrawTexture(lostText, 0, 0, WHITE);
                    exitWinnerScreen.Draw(170, 90);
                EndDrawing();
            }
            score_player1 = 0;
            score_player2 = 0;
            game_mod = -1;
        }
    }
}

//Função responsável por reinicializar o jogo após a realização de um ponto.
void Gaming::reinitGame(){
    ball.setCirclePosition(640, 400);
    racketPlayer.setRacketPosition(1250,340);
    racketComputer.setRacketPosition(10, 340);
    racketPlayer2.setRacketPosition(10, 340);
    std::this_thread::sleep_for(std::chrono::seconds(3)); //Pausa a thread durante um intervalo de 3 segundos.
}

//Função responsável por construir e ficar reconstruindo a tela do jogo para dar a sensação de movimento.
void Gaming::drawingObjects(int screen_width, int screen_heigh, int score_player1, int score_player2, int game_mod){
        BeginDrawing();
        ClearBackground(green);
        DrawLine(screen_width/2, 0, screen_width/2, screen_heigh, WHITE);
        ball.drawnCircle();
        racketPlayer.DrawRacket(WHITE);
        if(game_mod==1){racketComputer.DrawRacket(WHITE);}
        if(game_mod==2){racketPlayer2.DrawRacket(WHITE);}
        DrawText(TextFormat("%d", score_player1), 740, 30, 80, WHITE);
        DrawText(TextFormat("%d", score_player2), 500, 30, 80, WHITE);
    EndDrawing();
}

//Função responsável por construir a tela inicial e verificar qual foi o modo de jogo selecionado.
int Gaming::initialScreen(Button player1, Button player2, Button exit, Button torneio, Texture2D texture){
 //Roda enquanto for true porque não existe uma necessidade de saída do while por condição, já que o return por si só já realiza isso. 
    while(true)
    {
        Vector2 mousePosition = GetMousePosition();
        bool mousePressed = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

        //Check for events:
        if(player1.isPressed(mousePosition, mousePressed)){ //Verifica se o botão para o modo 1 jogador foi pressionado.
            return 1;
        }

        if(player2.isPressed(mousePosition, mousePressed)){ //Verifica se o botão para o modo 2 jogadores foi pressionado.
            return 2;
        }

        if(torneio.isPressed(mousePosition, mousePressed)){
            tournamentModeScreen();
        }

        if(exit.isPressed(mousePosition, mousePressed)){ //Verifica se o botão para sair do jogo foi pressionado.
            UnloadTexture(texture);
            return 0;
        }

        //Drawing objects:
        BeginDrawing();
        ClearBackground(this->green);
        DrawTexture(texture, 0, 0, WHITE); //Desenha o background com base na textura.
        player1.Draw(170,90);
        player2.Draw(170,90);
        exit.Draw(170,90);
        torneio.Draw(170,90);
        EndDrawing();
    }
}

void Gaming::checkScore(int check_score, int *score_player1, int *score_player2){
    if(check_score==1){
            *score_player1+=1;
            this->pontoMarcado = true;
        }

        if(check_score==2){
            *score_player2+=1;
            this->pontoMarcado = true;
        }
}

void Gaming::tournamentModeScreen(){

    int numJogadores = 4;

    Texture2D textTournamentScreen = geraTextura("graphics/tournament_screen.png");

    Button left_arrow{"graphics/seta_esquerda.png", {490, 550}};
    Button right_arrow{"graphics/seta_direita.png",  {720, 550}};
    Button confirm_button{"graphics/ok_button.png", {585, 620}};
  

    while(WindowShouldClose()==false){

        Vector2 mousePositionTournament = GetMousePosition();
        bool mousePressedTournament = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

        if(right_arrow.isPressed(     // dadosJogador.resize(numJogadores);
        mousePositionTournament, mousePressedTournament) && numJogadores <= 4){
            numJogadores*=2;
        }

        if(left_arrow.isPressed(mousePositionTournament, mousePressedTournament) && numJogadores > 4){
            numJogadores=numJogadores/2;
        }

        if(confirm_button.isPressed(mousePositionTournament, mousePressedTournament)){
            Dados *vetorJogadores = new Dados[numJogadores];
            setPlayerInformationScreen(vetorJogadores, numJogadores);   
            gamingLogicTournament(vetorJogadores, numJogadores);
            return;   
        }

        BeginDrawing();
        ClearBackground(this->green);
        DrawTexture(textTournamentScreen, 0, 0, WHITE);
        left_arrow.Draw(75,60);
        DrawText(TextFormat("%d JOGADORES", numJogadores), 556, 570, 25, WHITE);
        right_arrow.Draw(75,60);
        confirm_button.Draw(120,60);
        EndDrawing();
    }

    CloseWindow();
}

void Gaming::setPlayerInformationScreen(Dados *dadosJogador, int numJogadores){

    Rectangle exampleColorRacket = {580, 500, 120, 20};

    Button left_arrow{"graphics/seta_esquerda.png", {490, 550}};
    Button right_arrow{"graphics/seta_direita.png",  {720, 550}};

    Texture2D customizeScreenTexture = geraTextura("graphics/customize_screen.png");

    std::map<std::string, Color> colorRacket = {{"White", WHITE}, {"Black", BLACK}, {"Blue", BLUE}, {"Pink", PINK}, {"Orange", ORANGE}, {"Red", RED}, {"Yellow", YELLOW}, {"SkyBlue", SKYBLUE}, {"Gold", GOLD}};
    auto mapReference = colorRacket.begin();

    Rectangle inputBox = {568, 615, 150, 40};
    Color boxColor = LIGHTGRAY;
    std::string inputText = "";
    bool isEditing = false;

    int idJogador=0;

    while(WindowShouldClose()==false && idJogador<numJogadores){

        Vector2 mousePositionCustomer = GetMousePosition();
        bool mousePressedCustomer = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

        if(left_arrow.isPressed(mousePositionCustomer, mousePressedCustomer) && mapReference!=colorRacket.begin()){
            mapReference--;
        }

        //std::next foi usado porque o .end() aponta para uma casa depois do último elemento existente no map. Sendo assim, para que o programa não tentasse acessar um posição inválidam, o std::next foi usado para limitar o incremento até o último elemento.  
        if(right_arrow.isPressed(mousePositionCustomer, mousePressedCustomer) && std::next(mapReference)!=colorRacket.end()){
            mapReference++;
        }
        
        //Detecta o clique do mouse no input de digitação.
        if(mousePressedCustomer){
            if(CheckCollisionPointRec(mousePositionCustomer, inputBox)){
                isEditing = true; //Ativa a edição.
            }else{
                isEditing = false; //Desativa a edição.
            }
        }

        //Captura a letra da tecla pressionada.
        if(isEditing){
            int pressLetter = GetCharPressed(); //GetCharPressed retorna a letra do input pressionado em tabela ASCII.
            while(pressLetter>0){
                if(pressLetter >= 32 && pressLetter <=126){
                    inputText += char(pressLetter);
                }
                pressLetter = GetCharPressed();
            }
        }

        //Detecta se foi pressionado o backspace para apagar caractere
        if(IsKeyPressed(KEY_BACKSPACE) && !inputText.empty()){
            inputText.pop_back();
        }

        //Atualiza a cor da caixa dependendo do estado
        boxColor = isEditing ? WHITE : LIGHTGRAY;

        if(IsKeyPressed(KEY_ENTER) && idJogador<numJogadores){
            dadosJogador[idJogador].name = inputText;
            dadosJogador[idJogador].racketColor = mapReference->second;
            inputText = "";
            idJogador++;
        }
            
        BeginDrawing();
        ClearBackground(green);
        DrawTexture(customizeScreenTexture, 0, 0, WHITE);

        DrawRectangleRec(exampleColorRacket,  mapReference->second);
        left_arrow.Draw(75,60);
        escreveNaTela(TextFormat("%s ", mapReference->first.c_str()), 640, 565, 35); //O TextFormat só aceita const char*, por isso a função "c_str()" foi utilizada, para converter std::string para uma string padrão C.
        right_arrow.Draw(75,60);

        //Desenhar caixa do input.
        DrawRectangleRec(inputBox, boxColor);
        DrawRectangleLinesEx(inputBox, 2, DARKGRAY);

        // Desenhar o texto na caixa
        DrawText(inputText.c_str(), inputBox.x + 10, inputBox.y + 15, 20, BLACK);

        EndDrawing();

    }
}

void Gaming::gamingLogicTournament(Dados *dadosJogador, int numJogadores){

    Texture2D winTournamentScreenTexture = geraTextura("graphics/winnerTournamentScreen.png");
    ball.setCircleRadius(20);
    ball.setCirclePosition(640, 400);
    Vector2 ball_position;



    racketPlayer.setRacketDimensions(20,120);
    racketPlayer.setRacketPosition(1250,340);

    racketPlayer2.setRacketDimensions(20, 120);
    racketPlayer2.setRacketPosition(10, 340);

    Button exit{"graphics/exit_button.png", {580, 450}};

    int partidasRodada = 0;
    int idJogador = 0;
    bool partidaIniciada = false;

    while(WindowShouldClose()==false){ 

        ball_position = ball.getCirclePosition();
     

        racketPlayer.updateRacketPositions();
        racketPlayer2.updateRacketPositions_pl2();

        if(partidaIniciada==false){
        
            for(int i = 3; i>0; i--){

                escreveNaTela(TextFormat("%s VS %s", dadosJogador[idJogador+1].name.c_str(), dadosJogador[idJogador].name.c_str()), 640, 220, 80);
                DrawText(TextFormat("A partida começa em: %d", i), 200, 300, 80, WHITE);

                BeginDrawing();

                ClearBackground(green);
                DrawLine(screen_width/2, 0, screen_width/2, screen_heigh, WHITE);
                ball.drawnCircle();
                racketPlayer.DrawRacket(dadosJogador[idJogador].racketColor);
                racketPlayer2.DrawRacket(dadosJogador[idJogador+1].racketColor);
                DrawText(TextFormat("%d", dadosJogador[idJogador].pontPartida), 740, 30, 80, WHITE);
                DrawText(TextFormat("%d", dadosJogador[idJogador+1].pontPartida), 500, 30, 80, WHITE);

                EndDrawing();   
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }    
            partidaIniciada = true;
        }

        bool colisionPlayer1 = (CheckCollisionCircleRec(ball.getCirclePosition(), ball.getCircleRadius(), 
        Rectangle{racketPlayer.getRacketPosition().x, racketPlayer.getRacketPosition().y, racketPlayer.getRacketDimensions().x, racketPlayer.getRacketDimensions().y}));

        if(colisionPlayer1){
            ball.setSpeedCollisionX();
        }

        bool colisionPlayer2 = (CheckCollisionCircleRec(ball.getCirclePosition(), ball.getCircleRadius(),
        Rectangle{racketPlayer2.getRacketPosition().x, racketPlayer2.getRacketPosition().y, racketPlayer2.getRacketDimensions().x, racketPlayer2.getRacketDimensions().y}));

        if(colisionPlayer2){
            ball.setSpeedCollisionX();
        }

        int checkScore = ball.updatePosition();
        // this->checkScore(checkScore, &dadosJogador[idJogador].pontPartida, &dadosJogador[idJogador+1].pontPartida);    

        bool vencedorPartida = (dadosJogador[idJogador].pontPartida==5||dadosJogador[idJogador+1].pontPartida==5);

        BeginDrawing();
            ClearBackground(green);
            DrawLine(screen_width/2, 0, screen_width/2, screen_heigh, WHITE);
            ball.drawnCircle();
            racketPlayer.DrawRacket(dadosJogador[idJogador].racketColor);
            racketPlayer2.DrawRacket(dadosJogador[idJogador+1].racketColor);
            DrawText(TextFormat("%d", dadosJogador[idJogador].pontPartida), 740, 30, 80, WHITE);
            DrawText(TextFormat("%d", dadosJogador[idJogador+1].pontPartida), 500, 30, 80, WHITE);
        EndDrawing();

        if(vencedorPartida){ //Verifica quem foi o vencedor da partida.
            if(dadosJogador[idJogador].pontPartida==1){
                dadosJogador[idJogador].victory = true; //Atribui ao elemento victory do jogador vitorioso para que depois ele possa ser transferido para próxima rodada.
                vencedorMensagem(dadosJogador, idJogador);
                dadosJogador[idJogador].pontPartida=0; //Zera para que ele possa disputar a próxima partida.
            }else{
                dadosJogador[idJogador+1].victory=true;
                vencedorMensagem(dadosJogador, idJogador);
                dadosJogador[idJogador+1].pontPartida=0;
            }

            partidasRodada++; //Variável incrementada para poder saber quando a rodada chegou ao fim. 
            idJogador+=2; //Incrementa para que a próxima partida de uma rodada possa acontecer. 
            partidaIniciada=false;
        }

        if(this->pontoMarcado){
            this->pontoMarcado = false;
            reinitGame();
        }

        if(partidasRodada==numJogadores/2){ //Responsável pelo avanço dos vencedores para a próxima rodada.

            partidasRodada = 0;
            idJogador=0;
            
            Dados *auxArr = new Dados[numJogadores/2]; //É redimensionado para o número de jogadores da próxima rodada.
            int aux = 0; //Auxilia no percorrer do auxArr.

            for(int i=0; i < numJogadores; i++){
                if(dadosJogador[i].victory==true){ //Percorre o vetor de jogadores da rodada e atribui a auxArr aqueles que venceram a patida.
                    auxArr[aux] = dadosJogador[i];
                    aux++;
                }
            }
            
            for (int i = 0; i < numJogadores/2; i++)
            {
                auxArr[i].victory=false; //Reinicializa a booleana de vitória para que eles possam disputar a próxima rodada.
            }

            delete[] dadosJogador;  // Libera a memória antiga
            dadosJogador = auxArr; // Atualiza dadosJogador com os jogadores da próxima rodada.

            if(numJogadores/2==1){
                while (true)
                {

                    bool mousePressed = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
                    Vector2 mousePosition = GetMousePosition();

                    if(exit.isPressed(mousePosition, mousePressed)){
                        break;
                    }
                    
                    BeginDrawing();
                        ClearBackground(green);
                        DrawTexture(winTournamentScreenTexture, 0, 0, WHITE);
                        escreveNaTela(TextFormat("Parabéns %s", dadosJogador[idJogador].name.c_str()), 640, 220, 80);
                        escreveNaTela(TextFormat("Você foi o vencedor!"), 640, 300, 80);
                        exit.Draw(170, 90);
                    EndDrawing();
                }
                delete[] auxArr;
                return;
                UnloadTexture(winTournamentScreenTexture);
            }else{
                avancarFaseScreen(dadosJogador, numJogadores/2);
            }
            numJogadores /= 2;
            reinitGame();
        }
    }
}

void Gaming::vencedorMensagem(Dados *dadosJogador, int idJogador){
    BeginDrawing();
            ClearBackground(green);
            racketPlayer.setRacketPosition(1250,340);
            racketPlayer2.setRacketPosition(10, 340);
            ball.setCirclePosition(640, 400);

            DrawLine(screen_width/2, 0, screen_width/2, screen_heigh, WHITE);
            ball.drawnCircle();

            racketPlayer.DrawRacket(dadosJogador[idJogador].racketColor);
            racketPlayer2.DrawRacket(dadosJogador[idJogador+1].racketColor);

            DrawText(TextFormat("%d", dadosJogador[idJogador].pontPartida), 740, 30, 80, WHITE);
            DrawText(TextFormat("%d", dadosJogador[idJogador+1].pontPartida), 500, 30, 80, WHITE);

            if(dadosJogador[idJogador].pontPartida==5){
                escreveNaTela(TextFormat("%s", dadosJogador[idJogador].name.c_str()), 640, 220, 80);
                DrawText(TextFormat("\n Venceu a partida"), 270, 250, 80, WHITE);
            }else{
                escreveNaTela(TextFormat("%s", dadosJogador[idJogador+1].name.c_str()), 640, 220, 80);
                DrawText(TextFormat("\n Venceu a partida"), 270, 250, 80, WHITE);
            }
    EndDrawing();
}

void Gaming::escreveNaTela(string texto, int posicaoX, int posicaoY, int fontSize){
       
        int margin = 40;

        while(MeasureText(texto.c_str(), fontSize) >= (this->screen_width - margin*2))
                {
                    fontSize--;
                }

        DrawText(texto.c_str(), posicaoX - (MeasureText(texto.c_str(), fontSize)/2), posicaoY, fontSize, WHITE);

}

Texture2D Gaming::geraTextura(string imagem){
    Image ScreenImage = LoadImage(imagem.c_str());
    ImageResize(&ScreenImage, 1280, 800);
    Texture2D ScreenTexture = LoadTextureFromImage(ScreenImage);
    UnloadImage(ScreenImage);

    return ScreenTexture;
}

void Gaming::avancarFaseScreen(Dados *dadosJogador, int numJogadores){

    Texture2D avancaFaseTexture = geraTextura("graphics/avancaramDeFaseScreen.png");

    int aux = 0;
    float velocidadeAnimacao = 2.0f; // Letras por segundo
    float tempoDecorrido = 0.0f;
    int caractExibidos = 0; // Número de caracteres a exibir
    int posicaoY = 300;

    while(true){  

        tempoDecorrido += GetFrameTime(); //Pega a taxa de frames em segundo
        caractExibidos = (int)(tempoDecorrido * velocidadeAnimacao); //


        BeginDrawing();
            ClearBackground(this->green);
            DrawTexture(geraTextura("graphics/avancFaseScreen.png"), 0, 0, WHITE);

            for (int i = 0; i < aux; i++) { 
                escreveNaTela(dadosJogador[i].name.c_str(), 640, 400 + i * 80, 80);
            }

            if (aux < numJogadores) {
                std::string textoAnimado = dadosJogador[aux].name.substr(0, caractExibidos);
                escreveNaTela(textoAnimado.c_str(), 640, 400 + aux * 80, 80);

                // Avança para o próximo jogador quando o nome atual é exibido completamente
                if (caractExibidos > (int)dadosJogador[aux].name.length()) {
                    tempoDecorrido = 0.0f; // Reinicia o tempo para o próximo jogador
                    caractExibidos = 0;   // Reinicia a contagem de caracteres
                    aux++;                // Avança para o próximo jogador
                }
            }

                           
        EndDrawing();

        if(aux==numJogadores){
            for(int i=0; i<3; i++){
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
            break;
        }
        UnloadTexture(avancaFaseTexture);
    }
}