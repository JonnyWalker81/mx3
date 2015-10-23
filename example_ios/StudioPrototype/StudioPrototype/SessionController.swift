//
// Created by Jonathan Rothberg on 10/22/15.
// Copyright (c) 2015 Jonathan Rothberg. All rights reserved.
//

import Foundation
import UIKit

class SessionController : UITabBarController, UITabBarControllerDelegate {
    var _sessionData: MX3StudioSessionCell? = nil
    var _studioClient: MX3StudioVm? = nil
    init(studioClient: MX3StudioVm, sessionCell: MX3StudioSessionCell){
        _sessionData = sessionCell
        _studioClient = studioClient
        super.init(nibName: nil, bundle: nil)
    }

    required init?(coder aDecoder: NSCoder){
        super.init(coder: aDecoder)
    }

    override func viewDidLoad() {
        self.view.backgroundColor = UIColor.greenColor()

        var sessionDocuments = SessionDocuments(studioClient: _studioClient!)
        var sessionAttendees = SessionAttendees(studioClient: _studioClient!)
        var sessionChats = SessionChats(studioClient: _studioClient!)

        var docItem = UITabBarItem(title: "Documents", image: nil, tag: 0)
        sessionDocuments.tabBarItem = docItem

        var attendeesItem = UITabBarItem(title: "Attendees", image: nil, tag: 1)
        sessionAttendees.tabBarItem = attendeesItem

        var chatItem = UITabBarItem(title: "Chats", image: nil, tag: 2)
        sessionChats.tabBarItem = chatItem

        self.viewControllers = [sessionDocuments, sessionAttendees, sessionChats]
    }

    //Delegate methods
    func tabBarController(tabBarController: UITabBarController, shouldSelectViewController viewController: UIViewController) -> Bool {
        print("Should select viewController: \(viewController.title) ?")
        return true;
    }

    func tabBarController(tabBarController: UITabBarController, didSelectViewController viewController: UIViewController){
        print("Selected View Controller: \(viewController.title)")
    }
}