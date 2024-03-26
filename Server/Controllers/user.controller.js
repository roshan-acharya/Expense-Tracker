const User=require('../Models/user.model')

//user signup

const PostUsers=async(req,res)=>{
    try{
        const{username,password}=req.body;
        const user= await User.create(req.body)
        res.status(200).json(user)
      }
      catch(e){
        res.status(500).json({messgae: e.messgae})
      }
}
module.exports={
    PostUsers
}