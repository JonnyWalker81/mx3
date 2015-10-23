//
// Created by Jonathan Rothberg on 10/22/15.
// Copyright (c) 2015 Jonathan Rothberg. All rights reserved.
//

import Foundation
import UIKit

class StudioNavigator : UINavigationController{
    public var StudioClient: MS3tudioVm? = nil

    override init(rootViewController: UIViewController){
        super.init(rootViewController: rootViewController)
    }

    required init?(coder aDecoder: NSCoder){
        super.init(coder: aDecoder)
    }

    override init(nibName nibNameOrNil: String?, bundle nibBundleOrNil: NSBundle?){
        super.init(nibName: nibNameOrNil, bundle: nibBundleOrNil)
    }

    override func viewDidLoad(){
        let httpImpl = MX3HttpObjc()
        let launcher = MX3ThreadLauncherObjc()
        let uiThread = MX3EventLoopObjc()
        StudioClient = MX3StudioVm.createStudioClient(httpImpl, uiThread: uiThread, launcher: launcher, studioObserver: self)
        StudioClient?.login("jrothberg@bluebeam.com", password: "kingcon0")
    }
}