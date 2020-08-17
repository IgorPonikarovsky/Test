const addon = require('bindings')('usercheck');
const express = require('express');
const app = express();
const path = require('path');

app.set('view engine', 'ejs');
app.set("views", path.join(__dirname, "views"));

//Парсер для обработки данных от формы
const bodyParser = require('body-parser');
const urlencodedParser = bodyParser.urlencoded({extended:false});


app.get('/', (require, response) => {
    response.render("index", {title : 'Проверка пользователя'});
});

app.post('/check', urlencodedParser, (require, response) => {
    //Проверка пользователя
    result = (addon.UserCheck(require.body.userName)) ? "Пользователь есть" : "Такого пользователя нет";
    response.render('result', {title : 'Результат', result : result});
});

app.listen(3000);