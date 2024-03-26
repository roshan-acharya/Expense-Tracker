const express = require('express')
const mongoose = require('mongoose');
const User=require('./Routes/User')
const app = express();

//import model


//middleware
app.use(express.json());

 //routes
app.use(User)

//Database Connect
mongoose.connect('mongodb+srv://admin:admin@expensetracker.iy0om5w.mongodb.net/Tracker?retryWrites=true&w=majority&appName=ExpenseTracker')
  .then(() => console.log('Connected!'))
  .catch(() => {
    console.log("error");
  })

app.listen(3000, () => {
  console.log("Server is running on port 3000");
})

