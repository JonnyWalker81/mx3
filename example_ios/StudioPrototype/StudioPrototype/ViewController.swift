//
//  ViewController.swift
//  StudioPrototype
//
//  Created by Jonathan Rothberg on 10/9/15.
//  Copyright © 2015 Jonathan Rothberg. All rights reserved.
//

import UIKit

class ViewController: UIViewController, UITableViewDataSource, UITableViewDelegate, MX3UserListVmObserver{
    private var CellIdentifier = "UserCellIdentifier"

    var usersTable = UITableView()
    var api = ViewController.makeApi()
    var handle: MX3UserListVmHandle? = nil
    var viewModel: MX3UserListVm? = nil
    var studioClient: MX3Studio? = nil

    class func makeApi() -> MX3Api {
        // give mx3 a root folder to work in
        // todo, make sure that the path exists before passing it to mx3 c++
        let documentsFolder = NSSearchPathForDirectoriesInDomains(NSSearchPathDirectory.DocumentDirectory, NSSearchPathDomainMask.UserDomainMask, true).last
        let fileUrl = documentsFolder! + "/mx3"
        let file = fileUrl

        let fileManager = NSFileManager.defaultManager()
        if (!fileManager.fileExistsAtPath(file)) {
            try! fileManager.createDirectoryAtPath(file, withIntermediateDirectories: false, attributes: nil)
        }

        let httpImpl = MX3HttpObjc()
        let uiThread = MX3EventLoopObjc()
        let launcher = MX3ThreadLauncherObjc()
        let api = MX3Api.createApi(file, uiThread: uiThread, httpImpl: httpImpl, launcher:launcher)

        if let apiVar = api {
            if (!apiVar.hasUser()) {
                print("No user found, creating one");
                apiVar.setUsername("djinni demo");
            }
        }
        return api!;
    }

    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.

        usersTable.translatesAutoresizingMaskIntoConstraints = false
        usersTable.delegate = self
        usersTable.dataSource = self
        usersTable.registerClass(UITableViewCell.self, forCellReuseIdentifier: CellIdentifier)

        view.addSubview(usersTable)

        let views = ["table":usersTable]

        let vertical = NSLayoutConstraint.constraintsWithVisualFormat("V:|-(22)-[table]-(22)-|", options: NSLayoutFormatOptions.AlignAllCenterX, metrics: nil, views: views)
        let tableWidth = NSLayoutConstraint.constraintsWithVisualFormat("H:|-[table]-|", options: NSLayoutFormatOptions.DirectionLeadingToTrailing, metrics: nil, views: views)

        self.view.addConstraints(tableWidth)
        self.view.addConstraints(vertical)

        handle = api.observerUserList()

        let httpImpl = MX3HttpObjc()
        let launcher = MX3ThreadLauncherObjc()
        studioClient = MX3Studio.createStudioClient(httpImpl, launcher: launcher)
        studioClient?.login("jrothberg@bluebeam.com", password: "password")
    }

    override func viewWillAppear(animated:Bool){
        handle?.start(self)
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }

    func onUpdate(changes: [AnyObject]?, newData newD:MX3UserListVm?){
        //print("onUpdate...")
        if(changes != nil){
            if let changeArr = changes as? [MX3ListChange] {
                //print("Handle if case...")
                self.usersTable.beginUpdates();
                for change in changeArr {
                    if (change.fromIndex >= 0 && change.toIndex >= 0) {
                        var indexes = [Int(0), Int(change.toIndex)]
                        let path = NSIndexPath(indexes: indexes, length: 2);
                        self.usersTable.reloadRowsAtIndexPaths([path], withRowAnimation:UITableViewRowAnimation.Automatic);
                    } else if (change.fromIndex >= 0) {
                        var indexes = [Int(0), Int(change.fromIndex)]
                        let path = NSIndexPath(indexes: indexes, length: 2);
                        self.usersTable.deleteRowsAtIndexPaths([path], withRowAnimation:UITableViewRowAnimation.Automatic);
                    } else {
                        var indexes = [Int(0), Int(change.fromIndex)]
                        let path = NSIndexPath(indexes: indexes, length: 2);
                        self.usersTable.insertRowsAtIndexPaths([path], withRowAnimation:UITableViewRowAnimation.Automatic);
                    }
                }
                self.viewModel = newD;
                self.usersTable.endUpdates();
            }

        }
        else{
            self.viewModel = newD
            self.usersTable.reloadData()
        }
    }

    func tableView(tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        if(self.viewModel != nil){
            if let vm = self.viewModel {
                return Int(vm.count())
            }
        }

        return 0
    }

    func tableView(tableView: UITableView, cellForRowAtIndexPath indexPath: NSIndexPath) -> UITableViewCell {
        let cell = tableView.dequeueReusableCellWithIdentifier(CellIdentifier, forIndexPath: indexPath)

        //cell.textLabel?.text = "Test"
        if let vm = self.viewModel {
            var cellData = vm.get(Int32(indexPath.row))
            cell.textLabel?.text = cellData?.name;
            cell.detailTextLabel?.text = "If you manage to get the deps right";
        }


        return cell
    }

    func tableView(tableView: UITableView, didSelectRowAtIndexPath indexPath: NSIndexPath) {
        //print("didSelectRow...")
        if let vm = self.viewModel{
            vm.deleteRow(Int32(indexPath.row))
        }
    }
}

