const express=require('express');
const router=express.Router();
const {PostUsers,CheckUsers}=require('../Controllers/user.controller')

router.post("/user/signup", PostUsers)
router.post("/user/login", CheckUsers)

module.exports=router;