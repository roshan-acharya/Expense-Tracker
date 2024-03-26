const express = require('express')
const mongoose = require('mongoose');
const app = express()

mongoose.connect('mongodb+srv://admin:admin@expensetracker.iy0om5w.mongodb.net/User?retryWrites=true&w=majority&appName=ExpenseTracker')
  .then(() => console.log('Connected!'))
  .catch(()=>{
    console.log("error");
  })

app.listen(3000,()=>{
    console.log("Server is running on port 3000");
})
app.get('/', (req, res) => {
  res.send('hello world')
})
