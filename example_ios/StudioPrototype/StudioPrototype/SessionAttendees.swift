//
// Created by Jonathan Rothberg on 10/22/15.
// Copyright (c) 2015 Jonathan Rothberg. All rights reserved.
//

import Foundation
import UIKit

class SessionAttendees : UIViewController, UITableViewDelegate, UITableViewDataSource {
    private var CellIdentifier = "AttendeesCellIdentifier"
    var _attendeesTable = UITableView()
    var _studioClient: MX3StudioVm? = nil

    init(studioClient: MX3StudioVm){
        _studioClient = studioClient
        super.init(nibName: nil, bundle: nil)
        self.title = "Attendees"
    }

    required init?(coder aDecoder: NSCoder){
        super.init(coder: aDecoder)
    }

    override func viewDidLoad(){
        self.view.backgroundColor = UIColor.redColor()

        _attendeesTable.translatesAutoresizingMaskIntoConstraints = false
        _attendeesTable.delegate = self
        _attendeesTable.dataSource = self
        _attendeesTable.registerClass(UITableViewCell.self, forCellReuseIdentifier: CellIdentifier)

        view.addSubview(_attendeesTable)

        let views = ["table":_attendeesTable]

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

        cell.textLabel?.text = "Test Attendee"
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