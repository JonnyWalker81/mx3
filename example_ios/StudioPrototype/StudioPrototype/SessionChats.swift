//
// Created by Jonathan Rothberg on 10/22/15.
// Copyright (c) 2015 Jonathan Rothberg. All rights reserved.
//

import Foundation
import UIKit

class SessionChats : UIViewController, UITableViewDataSource, UITableViewDelegate {
    private var CellIdentifier = "ChatCellIdentifier"
    var _chatTable = UITableView()
    var _studioClient: MX3StudioVm? = nil

    init(studioClient: MX3StudioVm){

        _studioClient = studioClient
        super.init(nibName: nil, bundle: nil)
        self.title = "Chats"
    }

    required init?(coder aDecoder: NSCoder){
        super.init(coder: aDecoder)
    }

    override func viewDidLoad(){
        self.view.backgroundColor = UIColor.magentaColor()

        _chatTable.translatesAutoresizingMaskIntoConstraints = false
        _chatTable.delegate = self
        _chatTable.dataSource = self
        _chatTable.registerClass(UITableViewCell.self, forCellReuseIdentifier: CellIdentifier)

        view.addSubview(_chatTable)

        let views = ["table":_chatTable]

        let vertical = NSLayoutConstraint.constraintsWithVisualFormat("V:|-(22)-[table]-(22)-|", options: NSLayoutFormatOptions.AlignAllCenterX, metrics: nil, views: views)
        let tableWidth = NSLayoutConstraint.constraintsWithVisualFormat("H:|-[table]-|", options: NSLayoutFormatOptions.DirectionLeadingToTrailing, metrics: nil, views: views)

        self.view.addConstraints(tableWidth)
        self.view.addConstraints(vertical)
    }

    func tableView(tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        /*if(self.studioClient != nil){
            if let vm = self.studioClient {
                return Int(vm.getSessionCount())
            }
        }
        */

        return 2
    }

    func tableView(tableView: UITableView, cellForRowAtIndexPath indexPath: NSIndexPath) -> UITableViewCell {
        let cell = tableView.dequeueReusableCellWithIdentifier(CellIdentifier, forIndexPath: indexPath)

        cell.textLabel?.text = "Test Chat"
        /*if let vm = self.studioClient {
            let cellData = vm.getSession(Int32(indexPath.row))
            cell.textLabel?.text = cellData?.sessionName;
            cell.detailTextLabel?.text = cellData?.sessionId;
        }
        */

        return cell
    }

    func tableView(tableView: UITableView, didSelectRowAtIndexPath indexPath: NSIndexPath) {
        print("didSelectRow...")
        /*if let vm = self.studioClient{
            let cellData = vm.getSession(Int32(indexPath.row))
            let sessionController = SessionController(sessionCell: cellData!)
            self.navigationController?.pushViewController(sessionController, animated: true)
        }
        */
    }
}