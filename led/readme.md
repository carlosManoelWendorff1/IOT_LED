Esse código representa a imaplementação de uma solução server-side para uma tecnologia de IOT, a ideia é que tanto o client-side,
por parte do usuário final como o Postman acesse e envie comandos, quanto um dispositivo se conecte no servidor e execute os comandos 
listados.

Para rodar essa aplicação basta rodar os seguintes comandos:

-   pip install -r requirements.txt
-   python app.py

obs:

    Como previsto nas boas práticas do desenvolvimento com a linguagem python recomendo rodar a aplicação em um ambiente virtual,
    para evitar a instalação das bibliotecas diretamente na máquina, para fazer isso basta seguir dessa forma:

    para máquinas windows:
        -   python -m venv venv
        -   venv\Script\activate.bat
    
    para máquinas linux:
        -   python -m venv venv
        -   source venv\bin\activate


Desenvolvido por Carlos Manoel Wendorff