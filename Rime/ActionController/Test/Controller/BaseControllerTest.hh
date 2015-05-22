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
    $this->mock_controller->greeting = "Hello World!";
  }
  
  protected function tearDown()
  {
    parent::tearDown();
  }
  
  public function testControllerInheritanceTree()
  {
    $this->assertInstanceOf('\Rime\ActionController\Implementation\iAbstractController',$this->mock_controller,
      "Mock Controller does not have iAbstractController in its inheritance tree"
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
  
  public function testSetClassVariables()
  {
    $this->assertEquals($this->mock_controller->getData()->count(),1,
      "Failed to insert class attribute into controller.data"
    );
  }
  
  public function testGetClassVariables()
  {
    $this->assertEquals($this->mock_controller->greeting,"Hello World!",
      "Failed to get controller class variable"
    );
    $this->setExpectedException('\Rime\ActionController\Exception\UndefinedProperty');
    $this->mock_controller->fake_greeting;
  }
  
  public function testDefaultRendererFormat()
  {
    $this->assertEquals($this->mock_controller->getRenderer()->getData()->count(),3,
      "Failed to set default render types to BaseController.renderer"
    );
  }
   
  public function testSetResponseDataTypes()
  {
    $this->mock_controller->respondTo( ($format) ==> {
      $format->json = true;
    });
    
    $this->assertEquals(true,$this->mock_controller->getRenderer()->json,
      "Unable to set response data types"
    );
  }
    
}