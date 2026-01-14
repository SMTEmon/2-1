All of our notes are markdown files, and to get the best experience, it is recommended that you use [Obsidian](https://www.obsidian.md) paired with this repo. 

### Pre-requisites: 

1. Obsidian
2. [Git](https://github.com/git-guides/install-git)

### Setup

1. On your computer, open Terminal in the destination where you want your notes to be in. 
2. Clone the repo: 
```
git clone https://www.github.com/SMTEmon/2-1
```
or, if you like ssh for some reason,
```
git clone git@github.com:SMTEmon/2-1.git
```

If you are using Git for the first time, you are on https. But regardless, you should still be able to clone. All GitHub wants is an authentication method. 

If you are prompted for a password, GitHub is actually asking for a [PAT](https://www.youtube.com/watch?v=Z5tMe_aD0Dw).
3. After you're done, open Obsidian, and choose the option: Open Folder as Vault
   ![[Obsidian Prompt.png]]
4. Now, open the folder you just cloned. 
5. You should be able to see some plugins getting installed. The only one you really care about is Git. You should see it in your side bar like this: 
   
   ![[Open Git Source Control.png]]

	6. If you don't see this. Go to Settings > Community Plugins > Turn On > Search for Git > Install > Enable
	   
	7. Since you're not a collaborator, you should not be able to push anything to the remote. But, you can still pull and be synced with the repo itself. If you add files yourself to your Obsidian, those will not be updated on the main repo. 
	   
	8. Upon opening the Git Source Control plugin menu from the left bar, you should see this menu on the right. 
	   
	   ![[Pasted image 20260115024513.png]]
	6. Every now and then you might see some changes appear on the changes tab. All you have to do is click the Commit and Sync button (Far left), or simply the Pull Button, and it will do everything for you. 
	   
	   You might see an error saying you cannot push. Don't worry about it. ;-)


   