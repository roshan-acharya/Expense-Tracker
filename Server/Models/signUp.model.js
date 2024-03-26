const mongoose = require('mongoose');
const signupSchema = mongoose.Schema({
    username: {
        type: Mixed,
        required: true,
    },
    password: {
        type: Mixed,
        required: true,
    }
})
const signUp=mongoose.model("User",signupSchema)