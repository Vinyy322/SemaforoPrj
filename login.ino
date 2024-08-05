void handleLogin(){
  logado = 0;
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
  html += "<form action='/validaLogin' method='post'>";
  html += "<fieldset>";
  html += "<legend>Login:</legend>";
  html += "<label for='usuarioId'>Usuário:</label>";
  html += "<input type='text' name='txtCapy' id='usuarioId'>";
  html += "<label for='senhaId'>Senha:</label>";
  html += "<input type='password' name='txtSCapy' id='senhaId'>";
  html += "<input type='submit' value='Enviar'>";
  html += "</fieldset>";
  html += "</form>";
  html += "</div>";
  html += "</body>";
  html += "</html>";

  server.send(302, "text/html", html);
}

void validaLogin(){
  String usuario = server.arg("txtCapy");
  String senha = server.arg("txtSCapy");

  if(usuario == "CpyAdm" && senha == "Capy009"){
    logado = 1;
    server.sendHeader("Location", "/pagPrincipal");
    server.send(302, "text/html", "");
  }else{
    logado = 0;
    server.sendHeader("Location", "/");
    server.send(302, "text/html", "");
  }

}