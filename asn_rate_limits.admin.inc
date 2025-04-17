<?php
/**
 * @file
 * Admin form to manage module settings
 *
 */

/**
 * Define the form for manage settings
 *
 */
function asn_rate_limits_form($form, &$form_state) {
  $config = config('asn_rate_limits.settings');

  $form['top'] = array(
    '#markup' => t('If a web crawler or even a person (except for logged
    in users) <u>exceeds all the limits during the time window</u> specified in the
    fields below, their IP address will be blocked <u>immediately without
    warning</u>. The requests and limits are checked on each cron run. In case
    an ASN is blocked during this regular check, all incoming requests are
    furtheron checked and IPs of the blocked ASN are immediately blocked.
    ASNs are automatically unblocked when they do not exceed the limits anymore
    during a regular check.'),
  );

  $url = url('admin/config/people/ip-blocking');
  $form['info'] = array(
    '#markup' => '<p>'. t('You can manage blocked IPs at  <a href="@url">this page</a>.', array('@url' => $url)) . '</p>',
  );

  $form['time_window'] = array(
    '#type' => 'number',
    '#title' => t('Time window in which below limits apply'),
    '#default_value' => $config->get('time_window'),
    '#min' => 1,
    '#max' => 60*3,
    '#step' => 1,
    '#attributes' => array('title' => array('values 1-100')),
    '#field_suffix' => 'minutes'
  );

  $form['ips_limit'] = array(
    '#type' => 'number',
    '#title' => t('Maximum allowed number of IPs per ASN'),
    '#default_value' => $config->get('ips_limit'),
    '#min' => 1,
    '#max' => 100,
    '#step' => 1,
    '#attributes' => array('title' => array('values 1-100')),
    '#field_suffix' => 'distinct IP addresses'
  );

  $form['hits_limit'] = array(
    '#type' => 'number',
    '#title' => t('Maximum allowed number of requests per IP or ASN'),
    '#default_value' => $config->get('hits_limit'),
    '#min' => 1,
    '#max' => 100,
    '#step' => 1,
    '#attributes' => array('title' => array('values 1-100')),
    '#field_suffix' => 'hits'
  );

  $form['time_limit'] = array(
    '#type' => 'number',
    '#title' => t('Maximum allowed execution time per IP or ASN'),
    '#default_value' => $config->get('time_limit'),
    '#min' => 1,
    '#max' => 100,
    '#step' => 1,
    '#attributes' => array('title' => array('values 1-100')),
    '#field_suffix' => 'seconds'
  );

  $form['server_load_limit'] = array(
    '#type' => 'number',
    '#title' => t('Maximum allowed current sever load'),
    '#default_value' => $config->get('server_load_limit'),
    '#min' => 1,
    '#max' => 16,
    '#step' => 1,
    '#attributes' => array('title' => array('values 1-16')),
    '#field_suffix' => 'cores'
  );

  $form['actions']['#type'] = 'actions';
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration'),
  );
  return $form;
}

/**
 * Implements hook_validate().
 */
function asn_rate_limits_form_validate($form, &$form_state) {
  $config = config('asn_rate_limits.settings');
}

/**
 * Implements hook_submit().
 */
function asn_rate_limits_form_submit($form, &$form_state) {
  $config = config('asn_rate_limits.settings');

  $config->set('time_window', trim($form_state['values']['time_window']));
  $config->set('ips_limit', (int) $form_state['values']['ips_limit']);
  $config->set('hits_limit', (int) $form_state['values']['hits_limit']);
  $config->set('time_limit', (int) $form_state['values']['time_limit']);
  $config->set('server_load_limit', (int) $form_state['values']['server_load_limit']);

  $config->save();
  backdrop_set_message(t('The configuration options have been saved.'));
}
