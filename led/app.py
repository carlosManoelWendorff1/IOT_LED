from flask import Flask, jsonify, request

app = Flask(__name__)

# Variável para armazenar o estado do LED (ligado ou desligado)
led_status = {
    "estado": "desligado"  # Estado inicial
}

# Rota para retornar comandos
@app.route('/comandos', methods=['GET'])
def get_comandos():
    comandos = {
        "comandos": [
            {"acao": "verificar"},  # Para verificar o estado do LED
            {"acao": "ligar"},      # Para ligar o LED
            {"acao": "desligar"}    # Para desligar o LED
        ]
    }
    return jsonify(comandos)

# Rota para definir o estado do LED
@app.route('/led/<acao>', methods=['POST'])
def set_led(acao):
    global led_status
    if acao == 'ligar':
        led_status['estado'] = 'ligado'
    elif acao == 'desligar':
        led_status['estado'] = 'desligado'
    return jsonify(led_status)

# Rota para verificar o estado do LED
@app.route('/led/status', methods=['GET'])
def led_status_check():
    return jsonify(led_status)

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)
