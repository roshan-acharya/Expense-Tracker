const express=require('express');
const router=express.Router();
const {PostUsers}=require('../Controllers/user.controller')

router.post("/user/signup", PostUsers)

module.exports=router;