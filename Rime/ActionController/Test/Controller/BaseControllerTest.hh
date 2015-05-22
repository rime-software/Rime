<?hh // strict

namespace Rime\ActionController\Test;

require_once 'MockController.hh';

class BaseControllerTest extends \PHPUnit_Framework_TestCase
{
  protected MockController $mock_controller;
    
  protected function setUp()
  {
    parent::setUp();
    $this->mock_controller = new \Rime\ActionController\Test\MockController;
  }
  
  protected function tearDown()
  {
    parent::tearDown();
  }
  
  public function testControllerInheritanceTree()
  {
    $this->assertInstanceOf('\Rime\ActionController\Controller\AbstractController',$this->mock_controller,
      "Mock Controller does not have AbstractController in its inheritance tree"
    );
    $this->assertInstanceOf('\Rime\ActionController\Controller\BaseController',$this->mock_controller,
      "Mock Controller does not have BaseController in its inheritance tree"
    );
  }
  
  public function testGetData()
  {
    $this->assertInstanceOf('HH\Map',$this->mock_controller->getData(),
      "Controller.getData does not return an instance of a Map"
    );
  }
    
}