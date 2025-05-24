import { Routes } from '@angular/router';
import { DestinationsComponent } from './destinations/destinations.component';
import { AddDestinationComponent } from './destinations/add-destination/add-destination.component';
import { EditDestinationComponent } from './destinations/edit-destination/edit-destination.component';

export const routes: Routes = [
  { path: '', component: DestinationsComponent },
  { path: 'add', component: AddDestinationComponent },
  { path: 'edit/:id', component: EditDestinationComponent },
  { path: '**', redirectTo: '' }
];
