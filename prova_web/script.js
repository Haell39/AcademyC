document.getElementById("formNotas").addEventListener("submit", function(event) {
    var nome = document.getElementById("nome").value;
    var nota = document.getElementById("nota").value;
    var mensagem = document.getElementById("mensagem");

    mensagem.textContent = "";
    mensagem.classList.remove("erro", "sucesso");

    if (nome.trim() === "") {
        event.preventDefault();
        mensagem.textContent = "Nome é obrigatório!";
        mensagem.classList.add("erro");
        return;
    }

    if (nota === "" || nota < 0 || nota > 10) {
        event.preventDefault();
        mensagem.textContent = "Nota deve estar entre 0 e 10!";
        mensagem.classList.add("erro");
        return;
    }
});