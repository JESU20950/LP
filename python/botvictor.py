# importa l'API de Telegram
import telegram
import funciones as fun
from telegram.ext import Updater
from telegram.ext import CommandHandler
from telegram.ext import MessageHandler
from telegram.ext import Filters

# Funciones bot
def start(bot, update):
    """Envia un mensaje de inicio basico"""
    bot.send_message(chat_id=update.message.chat_id, text="Bienvenido a GraphBot.")

def help(bot, update):
    """Envia un mensaje con la lista de posible comandos y sus explicaciones"""
    mensaje = ("GraphBot te responderá, gráfica o textualmente, a las preguntas que" +
        " tengas relacionadas con grafos geométricos sobre la población de la tierra.\n" +
        "Dispondras de los siguientes comandos:\n\n" +
        "\"/help\" : Explicación del bot y comandos disponibles. Sin parámetros.\n" +
        "\"/author\" : Nombre y correo del creador del bot. Sin parámetros.\n" +
        "\"/graph *distance* *population*\" : Inicializa un nuevo grafo con las ciudades a *distance* Km de tu posición" +
        " y con poblacion superior a *population*. *population* ha de ser mayor que 30000 .\n" +
        "\"/nodes\" : Escribe el número de nodos en el grafo. Sin parámetros.\n" +
        "\"/edges\" : Escribe el número de aristas en el grafo. Sin parámetros.\n" +
        "\"/components\" : Escribe el número de componentes conexos en el grafo. Sin parámetros.\n" +
        "\"/plotpop *distance* latitude longitude\" : Muestra un mapa con todas las ciudades del" +
        " grafo con distancia menor o igual que *distance* de *latitude*, *longitude*. El parámetro *distance*" +
        " es obligatorio. El parámetro latitude y longitude es opcional, por defecto será la posición del usuario.\n" +
        "\"/plotgraph *distance* latitude longitude\" : Muestra un mapa con todas las ciudades del" +
        " grafo con distancia menor o igual que *distance* de *latitude*, *longitude* junto a las aristas que la conecetan. El parámetro *distance*" +
        " es obligatorio. El parámetro latitude y longitude es opcional, por defecto será la posición del usuario.\n" +
        "\"/route *source* *destination*\" : Muestra un mapa con las aristas del camino mas corto para ir de la ciudad *source* a la ciudad *destination.*" +
        " Todos los parámetros son obligatorios. Ambos parámetros se escribirán de la forma: *nombre*, *codigo_pais*")
    bot.send_message(chat_id=update.message.chat_id, text=mensaje, parse_mode=telegram.ParseMode.MARKDOWN)

def aux(bot, update, args):
    """Envia un mensaje con la lista de posible comandos y sus explicaciones"""
    print("a")
    print(args[0])
    mensaje = " "
    bot.send_message(chat_id=update.message.chat_id, text=mensaje, parse_mode=telegram.ParseMode.MARKDOWN)

def author(bot, update):
    mensaje = "Bot creado por Victor Vidal Rojas Condori (victor.vidal.rojas@est.fib.upc.edu)."
    bot.send_message(chat_id=update.message.chat_id, text=mensaje, parse_mode=telegram.ParseMode.MARKDOWN)

def graph(bot, update, args):
    try:
        a1 = float(args[0])
        a2 = float(args[1])
        if a2 < 30000:
            raise ValueError('Poblacion menor a 30000')
        if len(args) > 2:
        #Eliminando este if, conseguiremos que graph solo coja los 2 primeros argumentos ignorando los demas        
            raise ValueError('Parametros incorrectos')
        mensaje = "Creando el grafo. Se avisará cuando finalice la creación"
        bot.send_message(chat_id=update.message.chat_id, text=mensaje, parse_mode=telegram.ParseMode.MARKDOWN)
        fun.leerArchivo(a1, a2)
        mensaje = "Grafo creado."
        bot.send_message(chat_id=update.message.chat_id, text=mensaje, parse_mode=telegram.ParseMode.MARKDOWN)
    except Exception as e:
        print(e)
        mensaje = "El comando es erróneo. Revise si los parámetros son correctos"
        bot.send_message(chat_id=update.message.chat_id, text=mensaje, parse_mode=telegram.ParseMode.MARKDOWN)

def grafoDefecto(bot, update):
    try:
        mensaje = "Creando el grafo. Se avisará cuando finalice la creación"
        bot.send_message(chat_id=update.message.chat_id, text=mensaje, parse_mode=telegram.ParseMode.MARKDOWN)
        fun.leerArchivo()
        mensaje = "Grafo creado."
        bot.send_message(chat_id=update.message.chat_id, text=mensaje, parse_mode=telegram.ParseMode.MARKDOWN)
    except Exception as e:
        print(e)
        mensaje = "El comando es erróneo. Revise si los parámetros son correctos"
        bot.send_message(chat_id=update.message.chat_id, text=mensaje, parse_mode=telegram.ParseMode.MARKDOWN)

def nodes(bot, update):
    try:
        g = fun.getGrafoActual()
        if g is None:
            mensaje = "No has creado ningún grafo. Se generará un grafo por defecto"
            bot.send_message(chat_id=update.message.chat_id, text=mensaje, parse_mode=telegram.ParseMode.MARKDOWN)            
            grafoDefecto(bot, update)
            g = fun.getGrafoActual()
        mensaje = "El número de nodos del grafo es: " + str(g.number_of_nodes())
        bot.send_message(chat_id=update.message.chat_id, text=mensaje, parse_mode=telegram.ParseMode.MARKDOWN)
    except Exception as e:
        print(e)
        mensaje = "El comando es erróneo. Revise si los parámetros son correctos"
        bot.send_message(chat_id=update.message.chat_id, text=mensaje, parse_mode=telegram.ParseMode.MARKDOWN)

def edges(bot, update):
    try:
        g = fun.getGrafoActual()
        if g is None:
            mensaje = "No has creado ningún grafo. Se generará un grafo por defecto"
            bot.send_message(chat_id=update.message.chat_id, text=mensaje, parse_mode=telegram.ParseMode.MARKDOWN)
            grafoDefecto(bot, update)
            g = fun.getGrafoActual()
        mensaje = "El número de aristas del grafo es: " + str(g.number_of_edges())
        bot.send_message(chat_id=update.message.chat_id, text=mensaje, parse_mode=telegram.ParseMode.MARKDOWN)
    except Exception as e:
        print(e)
        mensaje = "El comando es erróneo. Revise si los parámetros son correctos"
        bot.send_message(chat_id=update.message.chat_id, text=mensaje, parse_mode=telegram.ParseMode.MARKDOWN)

def components(bot, update):
    try:
        g = fun.getGrafoActual()
        if g is None:
            mensaje = "No has creado ningún grafo. Se generará un grafo por defecto"
            bot.send_message(chat_id=update.message.chat_id, text=mensaje, parse_mode=telegram.ParseMode.MARKDOWN)
            grafoDefecto(bot, update)
            g = fun.getGrafoActual()
        mensaje = "El número de componentes conexos del grafo es: " + str(len(fun.getCC()))
        bot.send_message(chat_id=update.message.chat_id, text=mensaje, parse_mode=telegram.ParseMode.MARKDOWN)
    except Exception as e:
        print(e)
        mensaje = "El comando es erróneo. Revise si los parámetros son correctos"
        bot.send_message(chat_id=update.message.chat_id, text=mensaje, parse_mode=telegram.ParseMode.MARKDOWN)

def guardarPos(bot, update, user_data):
    try:
        msg = update.message
        user_data['lat'] = msg.location.latitude 
        user_data['lon'] = msg.location.longitude
        mensaje = "Posición guardada con éxito"
        bot.send_message(chat_id=update.message.chat_id, text=mensaje, parse_mode=telegram.ParseMode.MARKDOWN)
        print(user_data['lat'])
        print(user_data['lon'])
    except Exception as e:
        print(e)
        mensaje = "No se ha podido guardar la posición"
        bot.send_message(chat_id=update.message.chat_id, text=mensaje, parse_mode=telegram.ParseMode.MARKDOWN)

def plotpop(bot, update, args, user_data):
    try:
        g = fun.getGrafoActual()
        if g is None:
            mensaje = "No has creado ningún grafo. Se generará un grafo por defecto"
            bot.send_message(chat_id=update.message.chat_id, text=mensaje, parse_mode=telegram.ParseMode.MARKDOWN)
            grafoDefecto(bot, update)
        if len(args) == 1:
            if 'lat' not in user_data or 'lon' not in user_data:
                mensaje = "No se ha encontrado ubicación por defecto. Es necesario pasar una ubicación por argumentos o compartir la unicación actual"
                bot.send_message(chat_id=update.message.chat_id, text=mensaje, parse_mode=telegram.ParseMode.MARKDOWN)
            else:
                fun.dibujarPlotpop(float(args[0]), user_data['lat'], user_data['lon'])
                bot.send_photo(chat_id=update.message.chat_id, photo=open('plotpop.png','rb'))
        elif len(args) == 3:
            fun.dibujarPlotpop(float(args[0]), float(args[1]), float(args[2]))
            bot.send_photo(chat_id=update.message.chat_id, photo=open('plotpop.png','rb'))
        else:
            raise ValueError('Parametros incorrectos')
    except Exception as e:
        print(e)
        mensaje = "El comando es erróneo. Revise si los parámetros son correctos"
        bot.send_message(chat_id=update.message.chat_id, text=mensaje, parse_mode=telegram.ParseMode.MARKDOWN)

def plotgraph(bot, update, args, user_data):
    try:
        g = fun.getGrafoActual()
        if g is None:
            mensaje = "No has creado ningún grafo. Se generará un grafo por defecto"
            bot.send_message(chat_id=update.message.chat_id, text=mensaje, parse_mode=telegram.ParseMode.MARKDOWN)
            grafoDefecto(bot, update)
        if len(args) == 1:
            if 'lat' not in user_data or 'lon' not in user_data:
                mensaje = "No se ha encontrado ubicación por defecto. Es necesario pasar una ubicación por argumentos o compartir la unicación actual"
                bot.send_message(chat_id=update.message.chat_id, text=mensaje, parse_mode=telegram.ParseMode.MARKDOWN)
            else:
                fun.dibujarPlotgraph(float(args[0]), user_data['lat'], user_data['lon'])
                bot.send_photo(chat_id=update.message.chat_id, photo=open('plotgraph.png','rb'))
        elif len(args) == 3:
            fun.dibujarPlotgraph(float(args[0]), float(args[1]), float(args[2]))
            bot.send_photo(chat_id=update.message.chat_id, photo=open('plotgraph.png','rb'))
        else:
            raise ValueError('Parametros incorrectos')
    except Exception as e:
        print(e)
        mensaje = "El comando es erróneo. Revise si los parámetros son correctos"
        bot.send_message(chat_id=update.message.chat_id, text=mensaje, parse_mode=telegram.ParseMode.MARKDOWN)

def route(bot, update):
    try:
        g = fun.getGrafoActual()
        if g is None:
            mensaje = "No has creado ningún grafo. Se generará un grafo por defecto"
            bot.send_message(chat_id=update.message.chat_id, text=mensaje, parse_mode=telegram.ParseMode.MARKDOWN)
            grafoDefecto(bot, update)
        if len(args) == 2:
            if 'lat' not in user_data or 'lon' not in user_data:
                mensaje = "No se ha encontrado ubicación por defecto. Es necesario pasar una ubicación por argumentos o compartir la unicación actual"
                bot.send_message(chat_id=update.message.chat_id, text=mensaje, parse_mode=telegram.ParseMode.MARKDOWN)
            else:
                fun.dibujarPlotgraph(float(args[0]), user_data['lat'], user_data['lon'])
                bot.send_photo(chat_id=update.message.chat_id, photo=open('plotgraph.png','rb'))
        else:
            raise ValueError('Parametros incorrectos')
    except Exception as e:
        print(e)
        mensaje = "El comando es erróneo. Revise si los parámetros son correctos"
        bot.send_message(chat_id=update.message.chat_id, text=mensaje, parse_mode=telegram.ParseMode.MARKDOWN)


# declara una constant amb el access token que llegeix de token.txt
TOKEN = open('token.txt').read().strip()

# crea objectes per treballar amb Telegram
updater = Updater(token=TOKEN)
dispatcher = updater.dispatcher

# indica que quan el bot rebi la comanda
dispatcher.add_handler(CommandHandler('start', start))
dispatcher.add_handler(CommandHandler('help', help))
dispatcher.add_handler(CommandHandler('author', author))
dispatcher.add_handler(CommandHandler('graph', graph, pass_args=True))
dispatcher.add_handler(CommandHandler('nodes', nodes))
dispatcher.add_handler(CommandHandler('edges', edges))
dispatcher.add_handler(CommandHandler('components', components))
dispatcher.add_handler(CommandHandler('plotpop', plotpop, pass_args=True, pass_user_data=True))
dispatcher.add_handler(MessageHandler(Filters.location, guardarPos, pass_user_data=True))
dispatcher.add_handler(CommandHandler('plotgraph', plotgraph, pass_args=True,pass_user_data=True))
dispatcher.add_handler(CommandHandler('route', route, pass_args=True))
dispatcher.add_handler(CommandHandler('aux', aux, pass_args=True))

# engega el bot
updater.start_polling()
