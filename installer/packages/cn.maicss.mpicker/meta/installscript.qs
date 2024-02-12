function Component()
{
    // default constructor
}
 
Component.prototype.createOperations = function()
{
    // call default implementation to actually install README.txt!
    component.createOperations();
    if (systemInfo.productType === "windows") {
        component.addOperation("CreateShortcut",
                                   "@TargetDir@/MPicker.exe",// target
                                   "@DesktopDir@/MPicker.lnk",// link-path
                                   "workingDirectory=@TargetDir@",// working-dir
                                   "iconPath=@TargetDir@/MPicker.exe","iconId=0",// icon
                                   "description=Color Picker");// description
 
    }
 
}