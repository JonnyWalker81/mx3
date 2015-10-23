//
// Created by Jonathan Rothberg on 10/22/15.
// Copyright (c) 2015 Jonathan Rothberg. All rights reserved.
//

import Foundation
import UIKit

class SessionDocuments : UIViewController, UITableViewDataSource, UITableViewDelegate {
    private var CellIdentifier = "DocumentsCellIdentifier"
    var _documentsTable = UITableView()
    var _studioClient: MX3StudioVm? = nil
    var _studioSessionDocumentsVm: MX3StudioSessionDocumentsVm? = nil

    init(studioClient: MX3StudioVm){

        _studioClient = studioClient
        super.init(nibName: nil, bundle: nil)
        self.title = "Documents"
    }

    required init?(coder aDecoder: NSCoder){
        super.init(coder: aDecoder)
    }

    override func viewDidLoad(){
        self.view.backgroundColor = UIColor.cyanColor()

        _documentsTable.translatesAutoresizingMaskIntoConstraints = false
        _documentsTable.delegate = self
        _documentsTable.dataSource = self
        _documentsTable.registerClass(UITableViewCell.self, forCellReuseIdentifier: CellIdentifier)

        view.addSubview(_documentsTable)

        let views = ["table":_documentsTable]

        let vertical = NSLayoutConstraint.constraintsWithVisualFormat("V:|-(22)-[table]-(22)-|", options: NSLayoutFormatOptions.AlignAllCenterX, metrics: nil, views: views)
        let tableWidth = NSLayoutConstraint.constraintsWithVisualFormat("H:|-[table]-|", options: NSLayoutFormatOptions.DirectionLeadingToTrailing, metrics: nil, views: views)

        self.view.addConstraints(tableWidth)
        self.view.addConstraints(vertical)

        _studioSessionDocumentsVm = _studioClient.getSessionDocumentsVm(self)
        _studioSessionDocumentsVm.getDocuments();
    }

    func OnDocumentsRetrieved(documents: [AnyObject]?){
        print("OnDocumentsRetrieved...")
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

        cell.textLabel?.text = "Test"
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
