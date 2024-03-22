const express = require('express')
const app = express()

// respond with "hello world" when a GET request is made to the homepage
app.listen(3000,()=>{
    console.log("Server is running on port 3000");
})
app.get('/', (req, res) => {
  res.send('hello world')
})
