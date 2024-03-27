const User = require('../Models/user.model')

//user signup

const PostUsers = async (req, res) => {
  try {
    const { username, password } = req.body;
    if (!username || !password) {
      return res.status(422).json({ error: "Credentials must be filled" });
    }
    else {
      try {
        const isUser = await User.findOne({ username: username });
        if (isUser) {
          return res.status(206).json({ error: "User already exists" });
        }
        // If user doesn't exist, proceed with further logic
      } catch (error) {
        console.error("Error checking for user:", error);
        return res.status(500).json({ error: "Internal Server Error" });
      }

      const user = await User.create(req.body)
      return res.status(200).json(user)
    }
  }
  catch (e) {
    res.status(500).json({ messgae: e.messgae })
  }
}

//user login
const CheckUsers=async(req,res)=>{
  const {username,password}=req.body;
  isUser=await User.findOne({username:username ,password:password})
  if(isUser){
    return res.status(200).json({messgae : "Credentials matched"})
  }
  else{
    return res.status(206).json({messgae:"Invalid credentials"})
  }
}
module.exports = {
  PostUsers,
  CheckUsers
}