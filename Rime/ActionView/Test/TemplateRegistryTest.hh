<?hh // strict

namespace Rime\ActionView;

class TemplateRegistryTest extends \PHPUnit_Framework_TestCase
{
  
  protected function setUp()
  {
    $this->template_registry = new \Rime\ActionView\Registry\TemplateRegistry;
  }


  public function testSetHasGet()
  {
    $foo = function () {
      return "Foo!";
    };
  
    $this->assertFalse($this->template_registry->has('foo'));
  
    $this->template_registry->set('foo', $foo);
    $this->assertTrue($this->template_registry->has('foo'));
  
    $this->template = $this->template_registry->get('foo');
    $this->assertSame($foo, $this->template);
  
    $this->setExpectedException('Rime\ActionView\Exception\TemplateNotFound');
    $this->template_registry->get('bar');
  }

  public function testSetString()
  {
    $this->template_registry->set('foo', __DIR__ . '/templates/foo_template.hh');
    $template = $this->template_registry->get('foo');
    $this->assertInstanceOf('Closure', $template);
  
    ob_start();
      $template();
    $actual = ob_get_clean();
    $expect = 'Hello Foo!';
    $this->assertSame($expect, $actual);
  }

}
