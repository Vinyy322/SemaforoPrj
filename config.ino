void handlePrin(){
  String html;
  html = "<!DOCTYPE html>";
  html += "<html lang='pt-BR'>";
  html += "<head>";
  html += "<meta charset='UTF-8'>";
  html += "<meta name='viewport' content='width=device-width, initial-scale=1.0'>";
  html += "<title>Semáforo</title>";
  html += "<style>";
  html += "body {";
  html += "background-color: rgb(199, 207, 207);";
  html += "}";
  html += ".green {";
  html += "background-color: rgb(18, 185, 18);";
  html += "}";
  html += ".ylw {";
  html += "background-color: rgb(206, 206, 14);";
  html += "}";
  html += "fieldset {";
  html += "width: 50%;";
  html += "height: 25vh;";
  html += "display: flex;";
  html += "flex-direction: column;";
  html += "justify-content: space-between;";
  html += "}";
  html += ".conteiner {";
  html += "width: 100%;";
  html += "display: flex;";
  html += "flex-direction: column;";
  html += "align-items: center;";
  html += "}";
  html += "</style>";
  html += "</head>";
  html += "<body>";
  html += "<div class='conteiner'>";
  html += "<h1>Console de controle de semáforo</h1>";
  html += "<form action='/configSemaforo'>";
  html += "<fieldset>";
  html += "<legend>Tempo semaforo 1:</legend>";
  html += "<label for='greenId1'>Verde:</label>";
  html += "<input type='number' name='txtGreen1' id='greenId1' class='green'>";
  html += "<label for='yellowId1'>Amarelo:</label>";
  html += "<input type='number' name='txtYellow1' id='yellowId1' class='ylw'>";
  html += "<input type='submit' value='Enviar'>";
  html += "</fieldset>";
  html += "</form>";
  html += "<form action='/configSemaforo'>";
  html += "<fieldset>";
  html += "<legend>Tempo semaforo 2:</legend>";
  html += "<label for='greenId2'>Verde:</label>";
  html += "<input type='number' name='txtGreen2' id='greenId2' class='green'>";
  html += "<label for='yellowId2'>Amarelo:</label>";
  html += "<input type='number' name='txtYellow2' id='yellowId2' class='ylw'>";
  html += "<input type='submit' value='Enviar'>";
  html += "</fieldset>";
  html += "</form>";
  html += " </div>";
  html += "</body>";
  html += "</html>";

  if(logado == 1){
    server.send(302, "text/html", html);
  }else{
    server.sendHeader("Location", "/");
    server.send(302, "text/html", "");
  }
}

void configSemaforo(){
  tempV1 = (atoi(server.arg("txtGreen1").c_str()) > 0)? atoi(server.arg("txtGreen1").c_str()) : tempV1;
  tempA1 = (atoi(server.arg("txtYellow1").c_str()) > 0)? atoi(server.arg("txtYellow1").c_str()) : tempA1;
  tempV2 = (atoi(server.arg("txtGreen2").c_str()) > 0)? atoi(server.arg("txtGreen2").c_str()) : tempV2;
  tempA2 = (atoi(server.arg("txtYellow2").c_str()) > 0)? atoi(server.arg("txtYellow2").c_str()) : tempA2;

  server.sendHeader("Location", "/paginaPrincipal");
  server.send(302, "text/html", "");
  }